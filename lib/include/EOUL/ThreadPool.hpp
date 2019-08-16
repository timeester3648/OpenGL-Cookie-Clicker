#pragma once

#include <deque>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <functional>

namespace EOUL::Util {

	class ThreadPool {

		private:

			unsigned int maxThreads;

			bool started = false;

			std::atomic<bool> done = false;
			std::atomic<bool> stopping = false;

			std::mutex mutex;

			std::vector<std::thread*> threads;
			std::deque<std::function<void ()>> tasks;

		public:

			inline ThreadPool(unsigned int maxThreads = 4u) : maxThreads(maxThreads) {

			}

			inline ~ThreadPool() {

				this->stop();
				this->wait();

			}

		private:

			inline void checkMaxThreads() {

				if (unsigned int(this->threads.size()) < this->maxThreads) {

					this->threads.push_back(new std::thread([this]() {

						while (!this->done && !this->stopping) {

							this->mutex.lock();

							if (this->tasks.empty()) {

								this->done = true;

								this->mutex.unlock();

								break;

							}

							auto task = std::move(this->tasks.front());

							this->tasks.pop_front();

							this->mutex.unlock();

							if (!this->stopping) {

								task();

							}

						}

					}));

				}

			}

		public:

			/* starts the thread pool and allocates the worker threads */
			inline void start() {

				if (this->started) {

					return;

				}

				this->started = true;

				this->threads.reserve(std::min(this->maxThreads, (unsigned int) this->tasks.size()));

				while (unsigned int(this->threads.size()) < this->maxThreads && this->threads.size() < this->tasks.size()) {

					this->checkMaxThreads();

				}

			}
			/* stops the thread pool and deallocates the worker threads */
			inline void stop() {

				this->stopping = true;

			}

			/* returns if there are no tasks left */
			inline bool isDone() const {

				return this->done;

			}

			/* 
				adds a task to the threadpool.
				launches new thread if the maximum amount of threads are not used 
			*/
			inline void addTask(std::function<void ()>&& task) {

				this->checkMaxThreads();

				this->tasks.push_back(task);

			}
			/*
				adds a task to the threadpool, moves the task.
				launches new thread if the maximum amount of threads are not used 
			*/
			inline void addTask(std::function<void()>& task) {

				this->checkMaxThreads();

				this->tasks.push_back(std::move(task));

			}
			/* 
				adds a task to the threadpool, copies the task.
				launches new thread if the maximum amount of threads are not used 
			*/
			inline void addTask(const std::function<void()>& task) {

				this->checkMaxThreads();

				this->tasks.push_back(task);

			}

			/* waits until all threads are done, then deletes them */
			inline void wait() {

				for (auto& thread : this->threads) {

					if (thread->joinable()) {

						thread->join();

						delete thread;

					}

				}

				this->threads.clear();
				this->threads.shrink_to_fit();

			}

			/* returns how many threads are allocated */
			inline unsigned int getThreadCount() const {

				return static_cast<unsigned int>(this->threads.size());

			}

	};

}