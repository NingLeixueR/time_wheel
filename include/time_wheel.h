#pragma once

#include <functional>
#include <thread>
#include <vector>
#include <map>
#include <iostream>
#include <array>
#include <mutex>
#include <cmath>

#include "threadtools.h"
#include "impl.h"

namespace ngl
{
	struct wheel_node;
	class wheel;

	struct wheel_parm
	{
		int64_t					m_timerstart	= 0;					// ��ʱ��������ʱ��
		int						m_ms			= 0;					// �״δ����ĺ���
		//int					m_intervalms	= 0;					// ��������ĺ���
		std::function<int(int64_t)>	m_intervalms	= nullptr;			// ��������ĺ���(���ݴ��ݽ�ȥ�Ĵ���ʱ�䷵���´δ����ļ��)
		int						m_count			= 0;					// ��������
		void*					m_pram			= nullptr;				// ͸������
		std::function<void(wheel_node*)> m_fun	= nullptr;				// ��ʱ�ص�����
	};

	struct wheel_node
	{
		using timecallback = std::function<void(wheel_node*)>;

		int64_t			m_timerid	= 0;
		bool			m_remove	= false;				// ��ʱ���Ƿ��Ƴ�
		wheel_node*		m_next		= nullptr;
		wheel_parm		m_parm;
	};

	struct time_wheel_config
	{
	public:
		int32_t m_time_wheel_precision	= 10;		// ��ʱ������  ��λ����
		int32_t m_time_wheel_bit		= 8;		// ʱ���ֵĲ���  2^etime_wheel_bit
		int32_t m_time_wheel_count		= 4;

		// ��ʱ����ͷ������ʼ֧�ֵ����ʱ��
		int64_t max_time()
		{
			int64_t lsum = 0;
			int64_t lprecision = m_time_wheel_precision;
			for (int i = 0; i < m_time_wheel_count; ++i)
			{
				lprecision *= std::pow(2, 8);
				lsum += lprecision;
			}
			return lsum;
		}

		double year()
		{
			return day() / 365.0;
		}

		double day()
		{
			double lnum = 24 * 60 * 60 * 1000;
			uint64_t lsum = max_time();
			return lsum / lnum;
		}
	};

	class time_wheel
	{
		friend class wheel;

		time_wheel(const time_wheel&) = delete;
		time_wheel& operator=(const time_wheel&) = delete;

		struct impl_time_wheel;
		ngl::impl<impl_time_wheel> m_impl_time_wheel;
	public:
		static int64_t getms();
		time_wheel(const time_wheel_config& aconfig = time_wheel_config(), bool aisthreadcallback = true);
		~time_wheel();

		//##��ȡ�ִ涨ʱ������
		inline int	count();

		//##�Ƿ�û������ִ�еĶ�ʱ��
		inline bool	empty();

		//##��ȡ�����������ĺ�����
		inline int64_t server_start_ms();

		//##��ȡ��������ǰ�ĺ�����
		inline int64_t server_current_ms();

		//##addtimer��Ӷ�ʱ��
		//  ����ֵ��ʱ��id   ��ʱ��id����0��Ч
		int64_t addtimer(const wheel_parm& apram);

		//##removetimer�Ƴ�ָ����ʱ��
		//  int atimerid  ��ʱ��id
		inline void removetimer(int64_t atimerid);

		//m_isthreadcallback == false
		std::shared_ptr<wheel_node> pop_node();
	};

	class twheel
	{
		twheel() = delete;
		static time_wheel m_wheel;
	public:
		static time_wheel& wheel()
		{
			return m_wheel;
		}
	};
}
