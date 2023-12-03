#include<iostream>
#include<stdlib.h>
#include<string>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;
void home()
{
        //function to display homescreen
        char a=219;
        system("COLOR 04");
        cout<<"\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t  ************************************\n";
        cout<<"\t\t\t\t\t  *        HOSPITAL MANAGEMENT       *\n";
        cout<<"\t\t\t\t\t  ************************************\n";
        cout<<"\t\t\t\t\t  |                                  |\n";
        cout<<"\t\t\t\t\t  |    DEVELOPED BY :                |\n";
        cout<<"\t\t\t\t\t  |                                  |\n";
        cout<<"\t\t\t\t\t  |    22PT10 - DUVARAKESH S S       |\n";
        cout<<"\t\t\t\t\t  |    22PT18 - NANDANA T            |\n";
        cout<<"\t\t\t\t\t  |                                  |\n";
        cout<<"\t\t\t\t\t  |__________________________________|\n\n";
        cout<<"\n\t\t\t\t\t  ";
        cout<<"             LOADING...\n";
        cout<<"\n\t\t\t\t\t  ";

        //Loop to display the Loading Part
        for (int i = 1; i <= 36; i++)
        {
            cout<<a;
            Sleep(50);
        }
        system("cls");

}

struct Node {
  int data;
  string name;
  string details;
  string op;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *NodePtr;

class RedBlackTree 
{
   public:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->details='0';
    node->name='0';
    node->op = '0';
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      preOrderHelper(node->left);
      cout << node->data << " "<<node->name<<" "<<node->details<<" "<<node->op<<endl;
      preOrderHelper(node->right);
    }
  }

    void loadDataIntoTree(RedBlackTree &bst) {
        ifstream inputFile("hospital.txt");
        if (!inputFile.is_open()) {
            cout << "Failed to open the file for reading." << endl;
            return;
        }

        int id;
        string name, details, op;
        while (inputFile >> id >> name >> details >> op) {
            bst.insert(id, name, details, op);
        }

        inputFile.close();
    }

    void sendfile(NodePtr node) {
    if (node != TNULL) {
        sendfile(node->left);
        filewrite(node->data,node->name,node->details,node->op);
        sendfile(node->right);
    }
  }
 void removeFromFile(int key) {
    ifstream inputFile("hospital.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file for reading." << endl;
        return;
    }

    string line;
    ofstream tempFile("temp.txt");

    while (getline(inputFile, line)) {
        int id;
        string name, detail, op;
        istringstream iss(line);
        if (iss >> id >> name >> detail >> op) {
            if (id != key) {
                tempFile << id <<" "<< name << " "<< detail << " "<< op << "\n";
            }
        }
    }

    inputFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    if (remove("hospital.txt") != 0 || rename("temp.txt", "hospital.txt") != 0) {
        cout << "Failed to update the file." << endl;
    }
 }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
    removeFromFile(key);
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
    void filewrite(int key,string name,string d,string op)
    {
        ofstream file("hospital.txt", ios::app);
        if (file.is_open()) {
            file << key <<" "<< name <<" "<< d <<" "<< op << "\n";
            file.close();
        } 
        else {
        cout << "Failed to open the file for writing." << endl;
        }
    }
  // Inserting a node
  void insert(int key,string name,string d,string op) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->name=name;
    node->details=d;
    node->op=op;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;
    

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

bool searchRecordByID(int id) {
    ifstream inputFile("hospital.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file for reading." << endl;
        return false;
    }

    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        int recordID;
        string name, detail, op;
        istringstream iss(line);
        if (iss >> recordID >> name >> detail >> op) {
            if (recordID == id) {
                cout << "\t\t\t\tID: " << recordID << std::endl;
                cout << "\t\t\t\tName: " << name << std::endl;
                cout << "\t\t\t\tDetails: " << detail << std::endl;
                cout << "\t\t\t\tOP/IP: " << op << std::endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "\t\t\t\tRecord with ID " << id << " not found." << std::endl;
    }

    inputFile.close();
    return found;
}

bool searchRecordByName(const string& nameToSearch) {
    ifstream inputFile("hospital.txt");
    if (!inputFile.is_open()) {
        cout << "\t\t\t\tFailed to open the file for reading." << std::endl;
        return false;
    }

    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        int id;
        string name, detail, op;
        istringstream iss(line);
        if (iss >> id >> name >> detail >> op) {
            if (name == nameToSearch) {
                std::cout << "\t\t\t\tID: " << id << std::endl;
                std::cout << "\t\t\t\tName: " << name << std::endl;
                std::cout << "\t\t\t\tDetails: " << detail << std::endl;
                std::cout << "\t\t\t\tOP/IP: " << op << std::endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "\t\t\t\tRecord with name " << nameToSearch << " not found." << std::endl;
    }

    inputFile.close();
    return found;
}
struct User {
    string username;
    string password;
};

// Function to read user credentials from a file
vector<User> readUserCredentials(const string& filename) {
    ifstream file(filename);
    vector<User> users;

    if (!file.is_open()) {
        cout << "Failed to open the file for reading." <<endl;
        return users;
    }

    User user;
    while (file >> user.username >> user.password) {
        users.push_back(user);
    }

    file.close();
    return users;
}

// Function to perform user login
bool login(const string& username, const string& password, const vector<User>& users) {
    for (const User& user : users) {
        if (username == user.username && password == user.password) {
            return true; // Credentials match
        }
    }
    return false; // Credentials do not match
}

void writeUserCredentials(const string& filename, const User& newUser) {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file.is_open()) {
        cout << "Failed to open the file for writing." << std::endl;
        return;
    }

    file << newUser.username << " " << newUser.password << std::endl;
    file.close();
}

// Function to check if a username is already taken
bool isUsernameTaken(const string& username, const vector<User>& users) {
    for (const User& user : users) {
        if (username == user.username) {
            return true;
        }
    }
    return false;
}


int main()
{
    home();

     vector<User> users = readUserCredentials("user_credentials.txt");

    string username, password;

    system("COLOR 05");
    int q;
    cout<<"\t\t\t\tEnter 1 to Register "<<endl;
    cout<<"\t\t\t\tEnter 2 to login "<<endl;
    cout<<"\t\t\t\tEnter the choice : ";
    cin>>q;
    if (q == 1) {
        std::string newUsername, newPassword;
        system("cls");
        cout << "\t\t\t\tRegistration Page" << std::endl;
        cout << "\t\t\t\tEnter a new username: ";
        cin >> newUsername;

        if (isUsernameTaken(newUsername, users)) {
            cout << "\t\t\t\tUsername already taken. Please choose another one." << std::endl;
        } else {
            cout << "\t\t\t\tEnter a new password: ";
            cin >> newPassword;
            
            User newUser;
            newUser.username = newUsername;
            newUser.password = newPassword;

            // Register the new user
            writeUserCredentials("user_credentials.txt", newUser);
            cout << "\t\t\t\tRegistration successful. Welcome, " << newUsername << "!" << std::endl;
        }
    } 
    
    if (q == 2) {
        string username, password;
        system("cls");
        cout << "\t\t\t\tLogin Page" << std::endl;
        cout << "\t\t\t\tEnter your username: ";
        cin >> username;
        cout << "\t\t\t\tEnter your password: ";
        cin >> password;

        if (login(username, password, users)) {
            cout << "\t\t\t\tLogin successful. Welcome, " << username << "!" << std::endl;
        } else {
            cout << "\t\t\t\tLogin failed. Please check your username and password." << std::endl;
            return 0;
        }
    }
    RedBlackTree bst;
    int n,id;
    string name,detail,op;
    system("COLOR 03");
    int opt;
    bool c = true;
    int delayMilliseconds = 2000; 
    Sleep(delayMilliseconds);
    system("cls");
    while(c==true)
    {
      cout<<endl<<endl;
      cout<<"\t\t\t\tEnter 1 to Insert New Patient Data "<<endl;
      cout<<"\t\t\t\tEnter 2 to Delete Patient Data from the file "<<endl;
      cout<<"\t\t\t\tEnter 3 to search the Patient Data by ID "<<endl;
      cout<<"\t\t\t\tEnter 4 to search the Patient Data by Name  "<<endl;
      cout<<"\t\t\t\tEnter 5 to delete Patient Data from tree "<<endl;
      cout<<"\t\t\t\tEnter the choice : ";
      cin>>opt;
      switch(opt)
      {
        case 1:
          {
            bst.loadDataIntoTree(bst);
            ofstream outputFile("hospital.txt", ios::trunc);

            cout<<"\t\t\t\tEnter the Number of New record to insert : ";
            cin>>n;
                for(int i=0;i<n;i++)
                {
                  cout<<"\t\t\t\tEnter the Patient ID : ";
                  cin>>id;
                  cout<<"\t\t\t\tEnter the Name : ";
                  cin>>name;
                  cout<<"\t\t\t\tEnter the Patient details : ";
                  cin>>detail;
                  cout<<"\t\t\t\tEnter the Patient (OP/IP) : ";
                  cin>>op;
                  bst.insert(id,name,detail,op);
                }
                bst.sendfile(bst.root);
                break;
          }
          case 2:
            {
                int i;
                cout<<"\t\t\t\tEnter the ID :";
                cin>>i;
                bst.removeFromFile(i);
                break;
            }
            case 3:
            {
              int searchID;
              cout << "\t\t\t\tEnter the ID to search: ";
              cin >> searchID;
              cout<<endl;
              if (searchRecordByID(searchID)) {
                cout << "\t\t\t\tRecord found!" << std::endl;
              }         
              else {
                cout << "\t\t\t\tRecord not found." << std::endl;
              }
              cout<<endl;
              break;
            }
            case 4:
            {
              string searchName;
              cout << "\t\t\t\tEnter the name to search: ";
              cin>>searchName;
              cout<<endl;
              if (searchRecordByName(searchName)) {
                cout << "\t\t\t\tRecord found!" << endl;
              } 
              else {
                  cout << "\t\t\t\tRecord not found." << endl;
              }
              cout<<endl;
              break;
            }
            case 5:
            {
                int i;
                cout<<"\t\t\t\tEnter the ID :";
                cin>>i;
                bst.deleteNode(i);
                break;
            }
            default :
            {
              home();
              c=false;
              break;
            }
        }
        int delayMilliseconds = 2000; 
        Sleep(delayMilliseconds);
        system("cls");

    }
    

}