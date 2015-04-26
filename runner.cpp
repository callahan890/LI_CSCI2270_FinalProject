//Final project
//Graph movie
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"MovieTree.h"
#include "graph.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[])
{
  MovieTree* database = new MovieTree();
  ALGraph<string, int> g; //graph

  std::ifstream in_file;
  string file;
    cout << "Enter file name\n<filename.txt>: ";
    cin >> file;
    in_file.open(file.c_str());

  if (in_file.is_open())
  {
    int rating, year, quantity;
    string title, buffer;
    while (!in_file.eof())
    {
      getline(in_file, buffer, ',');
      rating = stoi(buffer);
      getline(in_file, buffer, ',');
      title = buffer;
      getline(in_file, buffer, ',');
	  g.insertAVertex(title);//insert the movie
      year = stoi(buffer);
      getline(in_file, buffer);
      quantity = stoi(buffer);
      database->addRawNode(rating, title, year, quantity);
    }
  }
  else
  {
    cout << file << "----File was not found. "<< endl;
    return 0;
    //could also -> while(!in_file.is_open()) {...requent new input... open()}
  }
  in_file.close();

  // read the file find out the length oh the graph
  cout << "Enter movie related file name\n<filename.txt>: ";
  cin >> file;
  in_file.open(file.c_str());

  if (in_file.is_open()){
	  string v1, v2;
	  while (!in_file.eof())
	  {
		  getline(in_file, v1, ',');
		  getline(in_file, v2);
		  g.insertAEdge(v1, v2, 1);
	  }
  }
  else
  {
    cout << file << "----File was not found. "<< endl;
    return 0;
    //could also -> while(!in_file.is_open()) {...requent new input... open()}
  }

  int select = -1;
  MovieNode* temp = nullptr;
  vector<string> ret;

  while (select != 6)
  {
    string title = "";
    cout << "======Main Menu=====" << endl
      << "1. Find a movie" << endl
      << "2. Rent a movie" << endl
      << "3. Print the inventory" << endl
	  << "4. Print related movie" << endl
	  << "5. List all with related" << endl
      << "6. Quit" << endl;

    cin >> select;
    switch (select)
    {
    case 1: //find a movie
      cout << "Enter title:" << endl;
      cin.ignore(1000, '\n');
      getline(cin, title);
      temp = database->search(title);
      if (temp == NULL || temp == nullptr)
        cout << "Movie not found." << endl;
      else
      {
        cout << "Movie Info:" << endl
          << "===========" << endl
          << "Ranking:" << temp->ranking << endl
          << "Title:" << temp->title << endl
          << "Year:" << temp->year << endl
          << "Quantity:" << temp->quantity << endl;
      }
      break;
    case 2: //rent a movie
      cout << "Enter title:" << endl;
      cin.ignore(1000, '\n');
      getline(cin, title);
      temp = database->search(title);
      if (temp == NULL || temp == nullptr)
      {
        cout << "Movie not found." << endl;
        break;
      }
      if (temp->quantity == 0)
      {
        cout << "Movie out of stock." << endl;
        break;
      }
      //database->rentMovie(title);
      temp->quantity--;
      cout << "Movie has been rented." << endl
        << "Movie Info:" << endl
        << "===========" << endl
        << "Ranking:" << temp->ranking << endl
        << "Title:" << temp->title << endl
        << "Year:" << temp->year << endl
        << "Quantity:" << temp->quantity << endl;
      break;
    case 3: //print inventory
      database->inorder_walk();
      break;
	case 4: //we are going to add new graph, search for graph, print the point 
	  cout << "Enter title:" << endl;
      cin.ignore(1000, '\n');
      getline(cin, title);
	  
	  if(g.showRelate(title, ret) == false){
		  cout << "Movie not found." << endl;
	  }else{
		  cout << "All movies related with " << title << " list below" << endl;
		  for(int i=0;i<(int)ret.size();i++){
			  temp = database->search(ret[i]);
			  cout << "Movie Info:" << endl
				   << "===========" << endl
				   << "Ranking:" << temp->ranking << endl
				   << "Title:" << temp->title << endl
				   << "Year:" << temp->year << endl
				   << "Quantity:" << temp->quantity << endl;
		  }
	  }
	  break;
	case 5: // print the whole graph
	  cout << g << endl;
	  break;
    case 6:
      cout << "Goodbye!" << endl;
      break;
    default://not an option
      cout << "That was not an option" << endl;
      break;
    }
  }
  if (temp != nullptr || temp != NULL)
    delete temp;
  delete database;
  return 0;
}
