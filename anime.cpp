#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

struct Anime_list{
    char anime_name[100];
    char completed;
    int recent_ep_watched;
    char manga;
    int recent_chap_read;
};

int main(){
    
    ifstream fi;
    ofstream fo;
    Anime_list al;
    char name[100], to_be_updated[100], to_be_deleted[100], updated_anime_name[100], updated_manga_status, mng, del, anime_completed;
    int ep, ch, choice, updated_episode, flag, mng_chap, updated_manga_chap;
    do{
        cout<<"\n1. Add \n2. Modify \n3. Display \n4. Delete \n5. Exit \nEnter your choice: ";
        cin>>ch;
        cin.clear();
        cin.sync();
        switch(ch){
            case 1:
                    cout<<"\n<----Add---->";
                    fo.open("anime.dat", ios::out | ios::binary | ios::app);
                    cout<<"\n Anime name: ";
                    cin.getline(name, 100);
                    cout<<" Have you completed the anime (y/n): ";
                    cin>>anime_completed;
                    
                    if(anime_completed == 'n'){
                        cout<<" Enter the recent episode watched: ";
                        cin>>ep;
                        al.recent_ep_watched = ep;
                    }

                    cout<<" Have you read the manga (y/n): ";
                    cin>>mng;

                    if(mng == 'y'){
                        cout<<" Enter recent manga chapter read: ";
                        cin>>mng_chap;
                        al.recent_chap_read = mng_chap;
                    }
                    else if(mng == 'n'){
                        al.recent_chap_read = 0;
                    }

                    strcpy(al.anime_name, name);
                    al.completed = anime_completed;
                    al.manga = mng;
                    
                    cout<<"\nWriting into binary file..."<<endl;
                    fo.write((char*)&al, sizeof(Anime_list));
                    fo.close();

                    if(!fo.good()){
                        cout<<"\nERROR OCCURED AT THE TIME OF WRITING!";
                        return 1;
                    }
                    cout<<"\n<----Exit---->";
                    break;
        
            case 2: 
                    flag = 0;
                    fi.open("anime.dat", ios::in | ios::binary);
                    if(!fi){
                        cout<<"\nERROR OCCURED WHILE OPENING THE FILE!";
                        return 1;
                    }
                    cout<<"\n<----Modify---->";
                    cout<<"\nEnter the name of the anime to be modified: ";
                    cin.getline(to_be_updated, 100);

                        while(fi.read((char*)&al, sizeof(al))){
                            if(strcmp(al.anime_name, to_be_updated) == 0){
                                flag = 1;
                                do{
                                    cout<<"\nWhat is to be updated? \n1. Anime name \n2. Episodes  \n3. Manga \n4. Exit";
                                    cout<<"\nEnter your choice: ";
                                    cin>>choice;
                                    cin.clear();
                                    cin.sync();
                                    switch(choice){
                                        case 1: 
                                                cout<<" Enter new anime name: ";
                                                cin.getline(updated_anime_name, 100);
                                                strcpy(al.anime_name, updated_anime_name);
                                                break;
                                        case 2: 
                                                if(al.completed == 'n'){
                                                    cout<<" Have you finished watching the anime: ";
                                                    cin>>anime_completed;
                                                    al.completed = anime_completed;
                                                    if(al.completed == 'n'){
                                                        cout<<" Enter recent episode watched: ";
                                                        cin>>updated_episode;
                                                        al.recent_ep_watched = updated_episode;
                                                    }
                                                }
                                                break;
                                        case 3: 
                                                if(al.manga == 'y'){
                                                    cout<<" Enter recent manga chapter read: ";
                                                    cin>>updated_manga_chap;
                                                    al.recent_chap_read = updated_manga_chap;
                                                }
                                                else if(al.manga == 'n'){
                                                    cout<<" Enter manga read status: ";
                                                    cin>>updated_manga_status;
                                                    al.manga = updated_manga_status;
                                                    if(updated_manga_status == 'y'){
                                                        cout<<" Enter recent manga chapter read: ";
                                                        cin>>updated_manga_chap;
                                                        al.recent_chap_read = updated_manga_chap;
                                                    }
                                                }
                                                break;   
                                    }
                                }while(choice != 4);

                                fo.open("update.dat", ios::out | ios::binary | ios::app);
                                fo.write((char*)&al, sizeof(Anime_list));
                                fo.close();
                            }
                            else{
                                fo.open("update.dat", ios::out | ios::binary | ios::app);
                                fo.write((char*)&al, sizeof(Anime_list));
                                fo.close();
                            }
                        }
                        if(!flag){
                                cout<<"RECORD NOT FOUND!";
                                return 1;
                        }
                    fi.close();
                    remove("anime.dat");
                    rename("update.dat", "anime.dat");
                    cout<<"\n<----Exit---->";
                    break;

            case 3:
                    cout<<"\n<----Display---->";
                    flag = 0;
                    fi.open("anime.dat", ios::in | ios::binary);
                    if(!fi){
                        cout<<"\nERROR OCCURED WHILE OPENING THE FILE!";
                        return 1;
                    }
                    while(fi.read((char*)&al, sizeof(Anime_list))){
                        cout<<"\n------------------------------------------------------------------\n\n";
                        cout<<"\tAnime name: "<<al.anime_name<<endl;
                        cout<<"\tAnime completed: "<<al.completed<<endl;
                        if(al.completed == 'n')
                            cout<<"\tRecent episode watched: "<<al.recent_ep_watched<<endl;
                        cout<<"\tManga read: "<<al.manga<<endl;
                        if(al.manga == 'y')
                            cout<<"\tRecent manga chapter read: "<<al.recent_chap_read<<endl;
                    }
                    fi.close();
                    cout<<"\n<----Exit---->";
                    break;

            case 4: 
                    cout<<"\n<----Delete---->";
                    cout<<"\nAre you sure you want to delete an anime from the list (y/n): ";
                    cin>>del;
                    cin.clear();
                    cin.sync();
                    if(del == 'y'){
                        fi.open("anime.dat", ios::in | ios::binary);
                        if(!fi){
                            cout<<"\nError in opening the file!";
                            return 1;
                        }
                        cout<<"\nEnter the name of the anime to be deleted: ";
                        cin.getline(to_be_deleted, 100);

                            while(fi.read((char*)&al, sizeof(al))){
                                if(strcmp(al.anime_name, to_be_deleted) == 0){
                                    flag = 1;
                                    cout<<"\nAnime removed from the list"<<endl;
                                }
                                else{
                                    fo.open("delete.dat", ios::out | ios::binary | ios::app);
                                    fo.write((char*)&al, sizeof(Anime_list));
                                    fo.close();
                                }
                            }
                            if(!flag){
                                cout<<"\n RECORD NOT FOUND!";
                                remove("delete.dat");
                                return 1;
                            }
                            fi.close();
                            remove("anime.dat");
                            rename("delete.dat", "anime.dat");
                    }
                    cout<<"\n<----Exit---->";                
                    break;
            case 5: 
                    cout<<".\n.\nExiting anime binary\n\n";
                    return 1; 
            default: 
                    cout<<"\nINVALID COMMAND\n";
                    break;
                       
        }
    }while(ch != 6);
return 0;
}
