#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>
using namespace std;


struct Anime_list{
    char anime_name[100]; //anime name
    int recent_ep_watched; //episode number
    char manga; //yes or no
};

int main(){
    
    ifstream fi;
    ofstream fo;
    Anime_list al; // object of the struct
    char name[100], mng, m_name[100], updated_anime_name[100], updated_manga_status;
    int ep, ch, choice, updated_episode, flag, pos;
    do{
        cout<<"\n1. Add \n2. Modify \n3. Display \n4. Exit \nEnter your choice: ";
        cin>>ch;
        switch(ch){
            case 1:
                    fo.open("anime-new.dat", ios::out | ios::binary | ios::app);
                    cout<<"Anime name: ";
                    cin>>name;
                    cout<<"Recent ep watched: ";
                    cin>>ep;
                    cout<<"Have you read the manga (y/n): ";
                    cin>>mng;

                    strcpy(al.anime_name, name);
                    al.recent_ep_watched = ep;
                    al.manga = mng;
                    
                    cout<<"\nWriting into binary file..."<<endl;
                    fo.write((char*)&al, sizeof(Anime_list));
                    fo.close();

                    if(!fo.good()){
                        cout<<"\nError occured at the time of writing!";
                        return 1;
                    }
                    break;
        
            case 2: 
                    flag = 0;
                    fi.open("anime-new.dat", ios::in | ios::binary);
                    //fo.open("temp.dat", ios::out | ios::binary | ios::app);
                    cout<<"\nEnter the name of the anime to be modified: ";
                    cin>>m_name;

                        while(fi.read((char*)&al, sizeof(al))){
                            if(strcmp(al.anime_name, m_name) == 0){
                                flag = 1;
                                do{
                                    cout<<"\nWhat is to be updated? \n1. Anime name \n2. Episodes watched \n3. Manga read \n4. Exit";
                                    cout<<"\nEnter your choice: ";
                                    cin>>choice;
                                    switch(choice)
                                    {
                                        case 1: cout<<"Enter new anime name: ";
                                                cin>>updated_anime_name;
                                                strcpy(al.anime_name, updated_anime_name);
                                                break;
                                        case 2: cout<<"Enter recent episode watched: ";
                                                cin>>updated_episode;
                                                al.recent_ep_watched = updated_episode;
                                                break;
                                        case 3: cout<<"Enter manga read status: ";
                                                cin>>updated_manga_status;
                                                al.manga = updated_manga_status;
                                                break;
                                    }
                                }while(choice != 4);
                                fo.open("temp.dat", ios::out | ios::binary | ios::app);
                                fo.write((char*)&al, sizeof(Anime_list));
                                fo.close();
                            }
                            else{
                                fo.open("temp.dat", ios::out | ios::binary | ios::app);
                                fo.write((char*)&al, sizeof(Anime_list));
                                fo.close();
                            }
                        }
                        if(!flag){
                                cout<<"Record not found!";
                                return 1;
                        }
                    fi.close();
                    remove("anime-new.dat");
                    rename("temp.dat", "anime-new.dat");
                    break;

            case 3:
                    fi.open("anime-new.dat", ios::in | ios::binary);
                    if(!fi){
                        cout<<"\nError in opening the file!";
                        return 1;
                    }
                        while(fi.read((char*)&al, sizeof(Anime_list))){
                            cout<<"\n-----------------------------------\n";
                            cout<<"Anime name: "<<al.anime_name<<endl;
                            cout<<"Recent episode watched: "<<al.recent_ep_watched<<endl;
                            cout<<"Manga read: "<<al.manga<<endl;
                        }
                    fi.close();
                    break;
        }
    }while(ch != 4);
    
    getch();
    return 0;
}
