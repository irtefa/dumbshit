

template <class T>
void Stack<T>::push(T const & a)
{
	//if(a!=NULL)
		myStack.push_front(a);
	// push front automatically increases the size of the list resize(size++);
}

template <class T>
T    Stack<T>::pop()
{
	T var = myStack.front();
	myStack.pop_front();
	return var;
}

template <class T>
T Stack<T>::peek() const
{
	return myStack.front();
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return myStack.empty();
}
