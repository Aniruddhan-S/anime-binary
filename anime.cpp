#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int add_anime(), update_anime(), display_anime(), delete_anime();
int add_manga(), update_manga(), display_manga(), delete_manga();
int clear(); 
//void error(const char* message[100]);

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
        cout<<"\n1. Anime \n2. Manga \n3. Exit \nEnter your choice: ";
        cin>>AnimeOrManga;
        clear();
        switch(AnimeOrManga){

            // Anime commands
            
                case 1: 
                        do{
                            cout<<"\n1. Add \n2. Modify \n3. Display \n4. Delete \n5. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: 
                                        clear();
                                        cout<<"\n<----Add---->";
                                        fo.open("anime.dat", ios::out | ios::binary | ios::app);

                                        add_anime();   
                                        
                                        cout<<"\nWriting into binary file..."<<endl;
                                        fo.write((char*)&al, sizeof(Anime_list));
                                        fo.close();

                                        if(!fo.good()){
                                            cout<<"\033[31;1m Error occured at the time of writing\033[0m";
                                            return 1;
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 2: 
                                        clear();
                                        flag = 0;
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\033[31;1m Error occured at the time of opening the file\033[0m";
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
                                                    cout<<"\033[31;1m Record not found\033[0m";
                                                    remove("update.dat");
                                                    fi.close();
                                                    break;
                                            }
                                        fi.close();
                                        remove("anime.dat");
                                        rename("update.dat", "anime.dat");
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 3:
                                        clear();
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\033[31;1m Error occured at the time of opening the file\033[0m";
                                            return 1;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_anime();
                                        
                                        cout<<"\n<----Exit---->";
                                        fi.close();
                                        break;

                                case 4: 
                                        clear();
                                        cout<<"\n<----Delete---->";
                                        cout<<"\nAre you sure you want to delete an anime from the list (y/n): ";
                                        cin>>del;
                                        cin.clear();
                                        cin.sync();
                                        if(del == 'y'){
                                            fi.open("anime.dat", ios::in | ios::binary);
                                            if(!fi){
                                                cout<<"\033[31;1m Error occured in oprning the file\033[0m";
                                                return 1;
                                            } 

                                            delete_anime();

                                            if(!flag){
                                                cout<<"\033[31;1m Record not found\033[0m";
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            fi.close();
                                            remove("anime.dat");
                                            rename("delete.dat", "anime.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                                
                                case 5: 
                                        cout<<".\n.\nExiting program\n\n";
                                        return 1; 

                                default: 
                                        cout<<"\033[31;1m Invalid command\033[0m";
                                        break;
                                        
                            }
                        }while(ch != 6);
                        break;

            // Manga commands
                
                case 2:
                        do{
                            clear();
                            cout<<"\n1. Add \n2. Update \n3. Display \n4. Delete \n5. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: 
                                        clear();
                                        cout<<"\n<----Add---->";
                                        fo.open("manga.dat", ios::out | ios::binary | ios::app);

                                        add_manga();   
                                        
                                        cout<<"\nWriting into binary file..."<<endl;
                                        fo.write((char*)&ml, sizeof(Manga_list));
                                        fo.close();

                                        if(!fo.good()){
                                            cout<<"\033[31;1m Error occured at the time of writing\033[0m";
                                            return 1;
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;
                                case 2: 
                                        clear();
                                        flag = 0;
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\033[31;1m Error occured while opening the file\033[0m";
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
                                                    cout<<"\033[31;1m Record not found\033[0m";
                                                    remove("update.dat");
                                                    fi.close();
                                                    break;
                                            }
                                        fi.close();
                                        remove("manga.dat");
                                        rename("update.dat", "manga.dat");
                                        cout<<"\n<----Exit---->";
                                        break;
                                case 3:
                                        clear();
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        if(!fi){
                                            cout<<"\033[31;1m Error occured while opening the file\033[0m";
                                            return 1;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_manga();
                                        
                                        cout<<"\n<----Exit---->";
                                        fi.close();
                                        break;
                                case 4:
                                        clear();
                                        cout<<"\n<----Delete---->";
                                        cout<<"\nAre you sure you want to delete a manga from the list (y/n): ";
                                        cin>>del;
                                        cin.clear();
                                        cin.sync();
                                        if(del == 'y'){
                                            fi.open("manga.dat", ios::in | ios::binary);
                                            if(!fi){
                                                cout<<"\033[31;1m Error occured while opening the file\033[0m";
                                                return 1;
                                            } 

                                            delete_manga();

                                            if(!flag){
                                                cout<<"\033[31;1;4m Record not found\033[0m";
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            fi.close();
                                            remove("manga.dat");
                                            rename("delete.dat", "manga.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                                case 5: 
                                        cout<<".\n.\nExiting program\n\n";
                                        return 1;
                                
                                default:
                                        cout<<"\033[31;1m Invalid Command\033[0m";   
                                        break;      
                            }
                        }while(ch != 6);
                        break;
                
                case 3: return 1;
                
                default: 
                        cout<<"\033[31;1m Invalid Command\033[0m";
                        //error("InvalidCommand");
                        break;
        }
    }while(AnimeOrManga != 4);
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
    char anime_completed, y_n, updated_anime_name[100];
    
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
                    else if(al.completed == 'y'){
                        cout<<" You have already completed watching the anime, contuining will set anime completed to 'no'";
                        cout<<"\nDo you want to continue? (y/n): ";
                        cin>>y_n;
                        if(y_n == 'y'){
                            al.completed = 'n';
                            cout<<"\n Anime completed status set to 'no'";
                            cout<<"\n Enter then season: ";
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

    cout<<"\n Enter the name of the anime to be deleted: ";
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&al, sizeof(Anime_list))){
            if(strcmp(al.anime_name, to_be_deleted) == 0){
                flag = 1;
                cout<<"\033[32;1m Anime removed from the list\033[0m";
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
    char manga_finished, y_n, updated_manga_name[100];
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
                    else if(ml.finished == 'y'){
                        cout<<" You have already completed reading the manga, contuining will set manga completed to 'no'";
                        cout<<"\n  Do you want to continue? (y/n): ";
                        cin>>y_n;
                        if(y_n == 'y'){
                            ml.finished = 'n';
                            cout<<"\n Manga completed status set to 'no'";
                            cout<<"\n Enter the recent chapter read: ";
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
                cout<<"\033[32;1m Manga removed from the list\033[0m";
            }
            else{ 
                fo.open("delete.dat", ios::out | ios::binary | ios::app);
                fo.write((char*)&ml, sizeof(Manga_list));
                fo.close();
            }
        }
return 0;
}

// miscellaneous functions

int clear(){
    cout<<"\x1B[2J\x1B[H";
return 0;
}

// void error(const char* message[100]){
//     char prefix[100], postfix[100];
//     strcpy(prefix, "\033[31;1;4m");
//     strcpy(postfix, "\033[0m");
//     strcat(prefix, message);
//     strcat(prefix,postfix);
//     cout<<prefix;
// }