import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.lang.reflect.*;
import static java.lang.System.*; 

class Prime {
    HashMap<Integer, Boolean> m_pn;

    public Prime()
    {
        m_pn = new HashMap<Integer, Boolean>();
    }

    public void checkPrime(int ...n)
    {
        boolean f = true;
        for(int i : n)
        {
	    Boolean isPrime = m_pn.get(i);
	    if(isPrime == null)
	    {
                isPrime = new Boolean((i == 2) ? true : false);
                for (int j = 2; j < i; ++j)
		{
                    if (i % j == 0)
		    {
                        break;
                    }
		    if (i / j < j)
		    {
                        isPrime = new Boolean(true);
			break;
		    }
		}
                m_pn.put(i, isPrime);
	    }
	    if (isPrime.booleanValue())
	    {
                if (f)
                {
                    System.out.printf("%d", i);
                    f = false;
                }
                else
                {
                    System.out.printf(" %d", i);
                }
            }
        }
        System.out.print('\n');
    }
}

public class Solution {

	public static void main(String[] args) {
		try{
		BufferedReader br=new BufferedReader(new InputStreamReader(in));
		int n1=Integer.parseInt(br.readLine());
		int n2=Integer.parseInt(br.readLine());
		int n3=Integer.parseInt(br.readLine());
		int n4=Integer.parseInt(br.readLine());
		int n5=Integer.parseInt(br.readLine());
		Prime ob=new Prime();
		ob.checkPrime(n1);
		ob.checkPrime(n1,n2);
		ob.checkPrime(n1,n2,n3);
		ob.checkPrime(n1,n2,n3,n4,n5);	
		Method[] methods=Prime.class.getDeclaredMethods();
		Set<String> set=new HashSet<>();
		boolean overload=false;
		for(int i=0;i<methods.length;i++)
		{
			if(set.contains(methods[i].getName()))
			{
				overload=true;
				break;
			}
			set.add(methods[i].getName());
			
		}
		if(overload)
		{
			throw new Exception("Overloading not allowed");
		}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
	
}
