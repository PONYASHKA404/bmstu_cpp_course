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

	bool empty() const noexcept { return size_ == 0; }

	size_t size() const noexcept { return size_; }

	~stack() { clear(); }

	template <typename... Args>	 // шаблон с переменным числом аргументов
	void emplace(Args&&... args)
	{
		tuta = new Case(tuta, std::forward<Args>(args)...);
		size_++;
	}

	void push(T&& value)  // в функцию передаётся ссылка на rvalue
	{
		tuta = new Case(tuta, std::move(value));
		size_++;
	}

	void push(
		const T& value)	 // в функцию передаётся константная ссылка на lvalue
	{
		tuta = new Case(tuta, value);
		size_++;
	}
	void clear() noexcept
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
		size_--;
	}

	T& top()
	{
		if (empty())
		{
			throw std::underflow_error("Тут пусто :(");
		}
		return tuta->shtuki;
	}

	const T& top() const  // второй const обозначает, что функция может
						  // использоваться только для чтения
	{  // возвращаем ссылку на последний элемент, через неё нельзя будет
	   // изменить, полученный элемент
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
