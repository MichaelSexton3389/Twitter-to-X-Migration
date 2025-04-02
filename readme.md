This is a project that I completed as a part of a course that reinforced my understanding of data structures in theory and in practice.


## Overview

This project focuses on implementing key data structures to efficiently store and manage tweet data as part of a simulated migration from Twitter to X. The implementation includes:

- **Hashing** with chaining for collision resolution
- **Binary Search Trees (BSTs)** for post storage
- **Min-Heaps** for initial tweet sorting

## Features

- **Hash Table with Chaining**: Users are stored in a hash table, and collisions are resolved using linked lists.
- **BST for Posts**: Each user has a BST to store their posts, with timestamps serving as keys.
- **Efficient Tweet Migration**: Tweets are processed from a min-heap and stored in the new structure.
- **User and Post Management**: Functionality to search users, insert new users/posts, and retrieve popular posts.

## How to Run

1. Clone the repository and navigate to the project directory.
2. Compile the program using:
   ```sh
   make
   ```
3. Run the executable:
   ```sh
   ./run_app <twitter_data.csv>
   ```
4. Use the menu-driven interface to interact with the system.

## Data Structures

### **User Representation (Hash Table Node)**
```cpp
struct XUser {
    string username;
    string userBio;
    int postCount;
    XUser* next;
    BST* bst;
};
```

### **Post Representation (BST Node)**
```cpp
struct XPost {
    int postedTime;
    string xContents;
    int likes;
    XPost* left;
    XPost* right;
};
```

### **Example Data Flow**
1. Tweets are initially stored in a **Min-Heap** sorted by timestamp.
2. Data is processed and inserted into the **Hash Table** (users).
3. Each user’s tweets are organized within a **BST** based on timestamps.

## Functionality

- **Insert User**: Adds a new user to the hash table, handling collisions.
- **Insert Post**: Places a tweet in the corresponding user’s BST.
- **Search User**: Locates a user in the hash table.
- **Display Posts**: Prints all posts by a user in timestamp order.
- **Most Liked Post**: Finds the most liked tweet in the dataset.

## Sample Output
```
User: himalaya_times
| Bio: Official Twitter handle of Himalaya Times National Daily
| Post Count: 1
| Posts:
1559027840:
---> "Tweet content here..."
```

## Project Structure
```
├── src/
│   ├── main.cpp
│   ├── hash.cpp
│   ├── bst.cpp
│   ├── minHeap.cpp
├── include/
│   ├── hash.hpp
│   ├── bst.hpp
│   ├── minHeap.hpp
├── data/
│   ├── twitter_data.csv
├── images/
│   ├── structureDiagram.png
│   ├── tweet_ex.png
├── Makefile
├── README.md
```

## Technologies Used
- **C++** for implementation
- **Makefile** for build automation
- **Linux Terminal** for execution

## Future Enhancements
- Implement **AVL Trees** for balanced post storage.
- Optimize **hash function** to minimize collisions.
- Add **Graph Representation** for user interactions.

---

This project showcases efficient data organization and retrieval techniques using multiple data structures. 🚀
