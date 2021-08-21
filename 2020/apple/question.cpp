void add(string make, string model, string color, string vin)
{
  
}
    
    
object[] get(make, model, color)
{

}

We insert a lot less than retrieve. Retriev API returns fixed size array.
Question: Datastructure to use.
Answer: Hashtable of fix size arrays. Re-allocate array on the insertion to get reduce time on retrieval.
