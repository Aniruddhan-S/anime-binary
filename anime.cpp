#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int add_anime(), update_anime(), display_anime(), delete_anime();
int add_manga(), update_manga(), display_manga(), delete_manga();

struct Anime_list{
    char anime_name[100];
    char completed;
    int season;
    int recent_ep_watched;
}al;

struct Manga_list{
    char manga_name[100];
    char finished;
    int recent_chap_read;
}ml;

ifstream fi;  
ofstream fo; 
int flag = 0;

int main(){

    char to_be_updated[100], updated_manga_status, del;
    int ch, updated_manga_chap, AnimeOrManga;
    do{
        cout<<"\n1. Anime \n2. Manga \nEnter your choice: ";
        cin>>AnimeOrManga;
        switch(AnimeOrManga){

            // Anime commands
            
                case 1: 
                        do{
                            cout<<"\n1. Add \n2. Modify \n3. Display \n4. Delete \n5. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: cout<<"\n<----Add---->";
                                        fo.open("anime.dat", ios::out | ios::binary | ios::app);

                                        add_anime();   
                                        
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

                                            while(fi.read((char*)&al, sizeof(Anime_list))){
                                                if(strcmp(al.anime_name, to_be_updated) == 0){
                                                    flag = 1;
                                                    
                                                    update_anime();

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
                                                    cout<<"\nRECORD NOT FOUND!\n";
                                                    remove("update.dat");
                                                    break;
                                            }
                                        fi.close();
                                        remove("anime.dat");
                                        rename("update.dat", "anime.dat");
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 3:
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\nERROR OCCURED WHILE OPENING THE FILE!";
                                            return 1;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_anime();
                                        
                                        cout<<"\n<----Exit---->";
                                        fi.close();
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

                                            delete_anime();

                                            if(!flag){
                                                cout<<"\n RECORD NOT FOUND!\n";
                                                remove("delete.dat");
                                                break;
                                            }
                                            fi.close();
                                            remove("anime.dat");
                                            rename("delete.dat", "anime.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                                
                                case 5: 
                                        cout<<".\n.\nExiting anime binary\n\n";
                                        break; 

                                default: 
                                        cout<<"\nINVALID COMMAND\n";
                                        break;
                                        
                            }
                        }while(ch != 6);
                        break;

            // Manga commands
                
                case 2:
                        do{
                            cout<<"\n1. Add \n2. Update \n3. Display \n4. Delete \n5. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: 
                                        cout<<"\n<----Add---->";
                                        fo.open("manga.dat", ios::out | ios::binary | ios::app);

                                        add_manga();   
                                        
                                        cout<<"\nWriting into binary file..."<<endl;
                                        fo.write((char*)&ml, sizeof(Manga_list));
                                        fo.close();

                                        if(!fo.good()){
                                            cout<<"\nERROR OCCURED AT THE TIME OF WRITING!";
                                            return 1;
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;
                                case 2: 
                                        flag = 0;
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\nERROR OCCURED WHILE OPENING THE FILE!";
                                            return 1;
                                        }
                                        cout<<"\n<----Modify---->";
                                        cout<<"\nEnter the name of the manga to be modified: ";
                                        cin.getline(to_be_updated, 100);

                                            while(fi.read((char*)&ml, sizeof(Manga_list))){
                                                if(strcmp(ml.manga_name, to_be_updated) == 0){
                                                    flag = 1;
                                                    
                                                    update_manga();

                                                    fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                    fo.write((char*)&ml, sizeof(Manga_list));
                                                    fo.close();
                                                }
                                                else{
                                                    fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                    fo.write((char*)&ml, sizeof(Manga_list));
                                                    fo.close();
                                                }
                                            }
                                            if(!flag){
                                                    cout<<"\nRECORD NOT FOUND!\n";
                                                    remove("update.dat");
                                                    break;
                                            }
                                        fi.close();
                                        remove("manga.dat");
                                        rename("update.dat", "manga.dat");
                                        cout<<"\n<----Exit---->";
                                        break;
                                case 3:
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\nERROR OCCURED WHILE OPENING THE FILE!";
                                            return 1;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_manga();
                                        
                                        cout<<"\n<----Exit---->";
                                        fi.close();
                                        break;
                                case 4:
                                        cout<<"\n<----Delete---->";
                                        cout<<"\nAre you sure you want to delete a manga from the list (y/n): ";
                                        cin>>del;
                                        cin.clear();
                                        cin.sync();
                                        if(del == 'y'){
                                            fi.open("manga.dat", ios::in | ios::binary);
                                            if(!fi){
                                                cout<<"\nError in opening the file!";
                                                return 1;
                                            } 

                                            delete_manga();

                                            if(!flag){
                                                cout<<"\n RECORD NOT FOUND!\n";
                                                remove("delete.dat");
                                                break;
                                            }
                                            fi.close();
                                            remove("manga.dat");
                                            rename("delete.dat", "manga.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                                case 5: 
                                        cout<<".\n.\nExiting manga binary";
                                        break;
                                
                                default:
                                        cout<<"\nINVALID COMMAND";         
                            }
                        }while(ch != 6);
                        break;
        }
    }while(AnimeOrManga != 3);
return 0;
}

// anime user defined functions

int add_anime(){
    char name[100], anime_completed;
    int anime_season, ep;

    cout<<"\n Anime name: ";
    cin.getline(name, 100);
    strcpy(al.anime_name, name);
    cout<<" Have you completed the anime (y/n): ";
    cin>>anime_completed;
    al.completed = anime_completed;
                    
    if(anime_completed == 'n'){
        cout<<" Enter the season: ";
        cin>>anime_season;
        al.season = anime_season;
        cout<<" Enter the recent episode watched: ";
        cin>>ep;
        al.recent_ep_watched = ep;
    }
return 0;
}

int update_anime(){
    int choice, updated_episode, updated_anime_season;
    char anime_completed, updated_anime_name[100];
    
    do{
        cout<<"\nWhat is to be updated? \n1. Anime name \n2. Episodes \n3. Exit";
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
                            cout<<" Enter the season: ";
                            cin>>updated_anime_season;
                            al.season = updated_anime_season;
                            cout<<" Enter recent episode watched: ";
                            cin>>updated_episode;
                            al.recent_ep_watched = updated_episode;
                        }
                    }
                    break;   
            }
    }while(choice != 3);
return 0;
}

int display_anime(){
    
    while(fi.read((char*)&al, sizeof(Anime_list))){
        cout<<"\n------------------------------------------------------------------\n\n";
        cout<<"\tAnime name ................. "<<al.anime_name<<endl;
        cout<<"\tAnime completed ............ "<<al.completed<<endl;
        if(al.completed == 'n'){
            cout<<"\tSeason ..................... "<<al.season<<endl;
            cout<<"\tRecent episode watched ..... "<<al.recent_ep_watched<<endl;
        }
    }
return 0;
}

int delete_anime(){
    char to_be_deleted[100];
    flag = 0;

    cout<<"\nEnter the name of the anime to be deleted: ";
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&al, sizeof(Anime_list))){
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
return 0;
}

// manga user defined functions

int add_manga(){
    char mng[100], fin;
    int mng_chap;

    cout<<"\n Enter the manga name: ";
    cin>>mng;
    strcpy(ml.manga_name, mng);
    cout<<" Have you completed reading the manga (y/n): ";
    cin>>fin;
    ml.finished = fin;
    if(fin == 'n'){
        cout<<" Enter recent manga chapter read: ";
        cin>>mng_chap;
        ml.recent_chap_read = mng_chap;
    }
return 0;
}

int update_manga(){
    char manga_finished, updated_manga_name[100];
    int choice, updated_chap;
    
    do{
        cout<<"\nWhat is to be updated? \n1. Manga name \n2. Episodes \n3. Exit\nEnter your choice: ";
        cin>>choice;
        cin.clear();
        cin.sync();
        switch(choice){
            case 1:
                    cout<<" Enter new manga name: ";
                    cin.getline(updated_manga_name, 100);
                    strcpy(ml.manga_name, updated_manga_name);
                    break;
            case 2: 
                    if(ml.finished == 'n'){
                        cout<<" Have you completed the manga (y/n): ";
                        cin>>manga_finished;
                        ml.finished = manga_finished;
                        if(ml.finished == 'n'){
                            cout<<" Enter the recent chapter read: ";
                            cin>>updated_chap;
                            ml.recent_chap_read = updated_chap;
                        }
                    }
                    break;
        }
    }while(choice != 3);
return 0;
}

int display_manga(){

    while(fi.read((char*)&ml, sizeof(Manga_list))){
        cout<<"\n------------------------------------------------------------------\n\n";
        cout<<"\tManga name ................. "<<ml.manga_name<<endl;
        cout<<"\tManga completed: ........... "<<ml.finished<<endl;
        if(ml.finished == 'n')
            cout<<"\tRecent manga chapter read .. "<<ml.recent_chap_read<<endl;
    }
return 0;
}

int delete_manga(){
    char to_be_deleted[100];
    flag = 0;

    cout<<"\nEnter the name of the manga to be deleted: ";
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&ml, sizeof(Manga_list))){
            if(strcmp(ml.manga_name, to_be_deleted) == 0){
                flag = 1;
                cout<<"\nManga removed from the list"<<endl;
            }
            else{ 
                fo.open("delete.dat", ios::out | ios::binary | ios::app);
                fo.write((char*)&ml, sizeof(Manga_list));
                fo.close();
            }
        }
return 0;
}
