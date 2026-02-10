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
	stack() : data_(nullptr), size_(0) {}  // создаём пустой стек

	bool empty() const noexcept
	{
		return size_ == 0;
	}  // проверяем пустой ли стек, noexcept

	size_t size() const noexcept
	{
		return size_;
	}  // проверка размера стека, size_t - целочисленный тип данных

	~stack()
	{  // диструктор
		for (size_t i = 0; i < size_; i++)
			data_[i].~T();
		::operator delete(data_);  // очищаем память без вызова диструктора
	}

	template <typename... Args>	 // шаблон с переменным числом аргументов
	void emplace(Args&&... args)
	{  // создание объекта в памяти без лишних копирований
		better_stack_version();
		new (data_ + size_) T(std::forward<Args>(
			args)...);	// позволяет перемещать rvalue (временные объекты, не
						// имеющие адреса в памяти, например: результат
						// выражения) и копировать lvaluer
		size_++;
	}

	void push(T&& value)  // в функцию передаётся ссылка на rvalue
	{
		better_stack_version();
		new (data_ + size_) T(std::move(value));
		size_++;
	}

	void push(
		const T& value)	 // в функци/ передаётся константная ссылка на lvalue
	{
		better_stack_version();
		new (data_ + size_) T(value);
		size_++;
	}
	void clear() noexcept { size_ = 0; }

	void pop()
	{  // удаляем последний элемент
		if (empty())
		{
			throw std::underflow_error(
				"Тут пусто :(");  // выдаём исключение, что стек пуст
		}
		size_--;
	}

	T& top()
	{  // возвращаем ссылку на последний элемент
		if (empty())
		{
			throw std::underflow_error("Тут пусто :(");
		}
		return data_[size_ - 1];
	}

	const T& top() const  // второй const обозначает, что функция может
						  // использоваться только для чтения
	{  // возвращаем ссылку на последний элемент, через неё нельзя будет
	   // изменить, полученный элемент
		if (empty())
		{
			throw std::underflow_error("Stack is empty!");
		}
		return data_[size_ - 1];
	}

   private:
	void
	better_stack_version()	// выделяем новое место для стека большего размера
	{
		T* new_place_ = (T*)::operator new(
			sizeof(T) *
			(size_ + 1));  // кол-во байт типа данных на новый размер
		for (size_t i = 0; i < size_; i++)
		{  // перемещение объектов в новую версию стека
			new (new_place_ + i) T(std::move(
				data_[i]));	 // определяем место и перемещаем в новый стек
			(data_ + i)->~T();	// уничтожаем объект в старом стеке
		}
		::operator delete(data_);  // очищаем старый стек
		data_ = new_place_;
	}

	T* data_;	   // указатель на начало стэка
	size_t size_;  // размер стэка
};
}  // namespace bmstu
