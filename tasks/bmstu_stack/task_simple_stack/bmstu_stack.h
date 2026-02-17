#pragma once

#include <exception>
#include <iostream>
#include <utility>

namespace bmstu
{
template <typename T>
class stack
{
   public:
	stack() : tuta(nullptr), size_(0) {}

	bool empty() const { return size_ == 0; }

	size_t size() const { return size_; }

	~stack() { clear(); }

	template <typename... Args>
	void emplace(Args&&... args)
	{
		tuta = new Case(tuta, std::forward<Args>(args)...);
		++size_;
	}

	void push(T&& value)
	{
		tuta = new Case(tuta, std::move(value));
		++size_;
	}

	void push(const T& value)
	{
		tuta = new Case(tuta, value);
		++size_;
	}
	void clear()
	{
		while (!empty())
		{
			pop();
		}
	}

	void pop()
	{
		if (empty())
		{
			throw std::underflow_error("Тут пусто :(");
		}
		Case* temp = tuta;
		tuta = tuta->next;
		delete temp;
		--size_;
	}

	T& top()
	{
		if (empty())
		{
			throw std::underflow_error("Тут пусто :(");
		}
		return tuta->shtuki;
	}

	const T& top() const
	{
		if (empty())
		{
			throw std::underflow_error("Stack is empty!");
		}
		return tuta->shtuki;
	}

   private:
	struct Case
	{
		T shtuki;
		Case* next;

		template <typename... Args>
		Case(Case* nextCase, Args&&... args)
			: shtuki(std::forward<Args>(args)...), next(nextCase)
		{
		}
	};

	size_t size_;
	Case* tuta;
};
}  // namespace bmstu
