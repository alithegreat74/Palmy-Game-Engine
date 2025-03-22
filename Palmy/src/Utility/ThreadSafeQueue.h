#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

namespace Palmy
{
	template <typename T>
	class ThreadSafeQueue {
	public:
		ThreadSafeQueue() = default;
		void TryPush(const T& newElement)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Queue.emplace(newElement);
			m_ConditionVariable.notify_one();
		}
		bool TryPop(T& element)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_ConditionVariable.wait(lock, [&]() {return !m_Queue.empty(); });
			element = std::move(m_Queue.front());
			m_Queue.pop();
			return true;
		}
		inline bool Empty() const { return m_Queue.empty(); }
	private:
		std::queue<T> m_Queue;
		std::mutex m_Mutex;
		std::condition_variable m_ConditionVariable;
	};
}