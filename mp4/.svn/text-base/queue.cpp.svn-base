template<class T> 
void Queue<T>::enqueue(T const & newItem)
{
	inStack.push(newItem); 	
}

template<class T> 
T Queue<T>::dequeue()
{
	if(outStack.isEmpty())
	{
		//if(inStack.isEmpty()) return NULL;
		while(!inStack.isEmpty())
		{
			outStack.push(inStack.pop());
		}
	}
	
	return outStack.pop();
}

template<class T>  
T Queue<T>::peek()
{
	if(outStack.isEmpty())
	{
		//if(inStack.isEmpty()) return NULL; // base case where inStack is empty // no elements at all
		while(!inStack.isEmpty())
		{
			outStack.push(inStack.pop());
		}
	}
	return outStack.peek();
}

template<class T>
bool Queue<T>::isEmpty() const
{
	if(inStack.isEmpty() && outStack.isEmpty())
		return true;
	return false;
}

