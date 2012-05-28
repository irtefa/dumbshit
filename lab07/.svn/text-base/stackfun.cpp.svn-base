
// sum
// adds all the elements in a stack
template <typename T>
T StackFun::sum(stack<T> & s)
{
    T total;
	if(s.empty())
		return 0;
	T var = s.top();
			s.pop();
	total =  var + sum(s);
	s.push(var);
	return total;
	// Your code here
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

// scramble
// reorders even sized blocks of items in the queue
// blocks start at size one and increases for each subsequent block
template <typename T>
void StackFun::scramble(queue<T> & q)
{
    stack<T> s;

	int n = 1;
	int count = 1;
	int var = (int)(q.size());
	while((count < var))
	{
		//for(int i=0; i < n ;i++)
		
		
			if(n%2==1)
			{
				//int i=0;
				for(int i=0; i < n &&(count <= var);i++)
				{
					q.push(q.front());
					q.pop();
					count++;
				 }
			}
			else
			{
				int i = 0;
				int p = 0;
				for( i=0; i < n && (count <= var);i++)
				{
					s.push(q.front());
					q.pop();
					p++;
					count++;
				}
				;
				for(int j=0; j < p; j++)
				{
					q.push(s.top());
					s.pop();
			        //count++;
				}
			}
		//count++;
		
		n++;
	
	//count++;
	}
				
    // optional: queue<T> q2;

    // Your code here
}

// verifySame
template <typename T>
bool StackFun::verifySame(stack<T> & s, queue<T> & q)
{	
	if(s.empty())
		return true;
	
	T temp = s.top();
	s.pop();
	
	 bool retval = verifySame(s,q);
	if(temp !=q.front())
		retval = false;
	q.push(q.front());
	q.pop();
	s.push(temp);
	return retval;

    //T temp1; // rename me
    //T temp2; // rename :)
    
    //return retval;
}

