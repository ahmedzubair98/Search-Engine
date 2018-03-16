# Search-Engine
This is a personal project which utilizes stl map and stl unordered map to store large amount of data and retrieve it. Wikipedia snapshot from 2010, converted into text file taken from (https://searchengineproject.wordpress.com/), was parsed and a seperate text file of each article was created. Each word in article was stored in map and unordered_map creating a search engine. There is a option of making query using map or hash table. When query is made difference in speed of map and unordered_map can be seen. 

Each word is stored as a struct which contains document name and position of that word in the document. As a word exists in many documents, vector of class word is stored as a value and the word itself as the key in both structures. unordered_map and mutimap are also further used during implementation of program.

Different type of queries are possible
1. W
- This is simplest query which consists of a single word.
- Documents are arranged in order of most occurence of word in document.
2. W W W ...
- This type of query can include many words.
- Documents are arranged in which most number of words exists in same file and further sorted in descending order of occurence of words in file. 
3. "W W W ..."
- This is sentence query meaning all words entered inside quotes must be in same position in a file.
- Documents are arranged in descending order of most occurences of sentence in document.
4. "W W W ..." W W ..
- This query combines query 2 and query 3.
- Documents are sorted in descending order of most number of words or sentences in query.
5. W W W ... - W W ..
- This query contains all documents  which include words before - and not words after - are not present.
- Documents are arranged in which most number of words exists in same file and further sorted in descending order of occurence of words in file.
6. "W W W ..." - W W W ...
- This query combines query 5 and query 4.
- Documents are sorted in descending order of most number of words or sentences in query.
