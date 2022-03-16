This program uses a custom Cow class that stores the id, weight, and milk
information of cow. There are methods to update the weight and milk values and 
print the cow's record. All of these methods run in O(1).

In the first part of the program, each line of the file is read individually. A
string stream is used to obtain the cow id, mode, and amount from each line. A 
std::unordered_map is used to store the cow data. This data uses a hash table 
internally so organise the data. Hash tables can insert in average case O(1), 
and this runs once for each record, so the average runtime is O(r).

After this, each cow in the hash table is moved into a std::vector, which uses 
an array list internally. Adding to the end of a vector is O(1) average case 
according to the documentation, although in rare cases it can be worse due to
reallocating memory. This applies to every cow, so this part is O(c). Then the 
list is sorted, which using std::sort takes O(c log c) time. Finally, all the
cows in the vector are printed in order, which takes O(c).

The final runtime is O(r) + O(c) + O(c log c) + O(c) = O(r + c log c).

Requires C++17 or later