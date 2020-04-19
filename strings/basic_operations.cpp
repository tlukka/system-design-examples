/*      basic_operations.cpp

1. TOKENIZING

2. CREATING string from int, string, double

3. TRAVERSAL: forward, reverse

4. SIZEOF STRING:
        str.length()                            str.size()
What  returns no of characters in string        same
Why     inbuilt for string class                                        to make consistent with other STL container
Complexity      O(1)                               O(1) 
 - Both are same anyone can be used.

5. SEARCHING:   find()

6. SUBSTRING:   substr()

7. TRUNCATING:  
   erase(): Erases portion of string, reducing its length
        erase(starting_pos, length)

8. INSERTING: Inserts additional characters into the string right before the character indicated by pos.
*/
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int main(){
        string s = "never give up", temp_str;

        //TOKENIZING
        stringstream ss(s);                     //Fed string to ss constructor
        while(getline(ss, temp_str, ' ')){              //Space tokenization
                cout<<temp_str<<" ";
                temp_str=temp_str+" ";
                cout<<endl;
        }
        /*O/P:
          never
          give
          up */


        //CREATING
        stringstream ssc;
        int a=4; string b="fail"; char c='e';
        ssc<<a<<b<<c;
        cout<<ssc.str()<<endl;
        /*O/P:
         4faile */


        //TRAVERSAL
        string str = "Fail early fail often";
        for (auto i=str.begin(); i!=str.end(); i++)
                cout<<*i;
        cout<<endl;
        for (auto i=str.rbegin(); i!=str.rend(); i++)    //Reverse iterator     
                cout<<*i;
        cout<<endl;
        /*O/P:
        Fail early fail often
        netfo liaf ylrae liaF */


        //SIZE
        string st = "LoveWork";
        cout<<st.size()<<endl;
        cout<<st.length()<<endl;
        /*O/P:
         8
         8 */


        //SEARCHING
        string str1 = "Failing Reveals your weaknesses!";
        cout<<str1.find("your")<<endl;
        /*O/P:
          16 */ //0th index of substring if found, else -1


        //SUBSTRING
        string str2="Fall in Love with Work, Money will follow";
        cout<<str2.substr(5,17)<<endl;
        /*O/P:
         in Love with Work */


        //TRUNCATING
        string str3="Hunger for Success";
        str3.erase(0, 7);               //Erase from index=0 to index=7
        cout<<str3<<", size="<<str3.size()<<endl;
        str3.erase(3, str3.size()-1);   //Erase from index=3 to end
        cout<<str3<<", size="<<str3.size()<<endl;
        /*O/P:
         for success, size=11
         for, size=3
         */

        //INSERTING
        string str4 = "your ass out";
        str4.insert(0, "work ");
        cout<<str4<<endl;
        /*O/P:
        work your ass out
        */
}
