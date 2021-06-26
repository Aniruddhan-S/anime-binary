#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int add_anime(), update_anime(), display_anime(), delete_anime();
int add_manga(), update_manga(), display_manga(), delete_manga(); 
void success(string success), error(string error), clear();
char* strip(char *name);
int anime_check(char *Aname), manga_check(char *Mname);

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

    char to_be_updated[100], updated_manga_status, del, existing_name[100], name_to_check[100]; 
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
 
                                        if(add_anime() == 1){
                                            fo.close();
                                            break;
                                        }  
                                        else{
                                            cout<<"\n Writing into binary file\n";
                                            fo.write((char*)&al, sizeof(Anime_list));
                                            fo.close();
                                        }

                                        if(!fo.good()){
                                            error("Error occured at the time of writing");
                                            return 1;
                                        }
                                        else if(fo.good()){
                                            success("Data entry successful");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 2: 
                                        clear();
                                        flag = 0;
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");
                                            break;
                                        }
                                        cout<<"\n<----Modify---->";
                                        cout<<"\nEnter the name of the anime to be modified: ";
                                        cin.getline(to_be_updated, 100);

                                            while(fi.read((char*)&al, sizeof(Anime_list))){
                                                strcpy(existing_name, al.anime_name);
                                                strcpy(name_to_check, to_be_updated);
                                                
                                                if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
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
                                            if(!fo.good()){
                                                error("Error occured at the time of writing");
                                            }
                                            else if(fo.good()){
                                                if(flag == 0){
                                                    error("Record not found");
                                                    remove("update.dat");
                                                    fi.close();
                                                    break;
                                                }
                                                else
                                                    success("Data updation successful");
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
                                            error("Error occured while opening the file / File does not exist");
                                            break;
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
                                                error("Error occured while opening the file / File does not exist");
                                                break;
                                            } 

                                            delete_anime();

                                            if(!flag){
                                                error("Record not found");
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            else{
                                                success("Anime removed from the list");
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
                                        error("Invalid command");
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
                                        clear();
                                        cout<<"\n<----Add---->";
                                        fo.open("manga.dat", ios::out | ios::binary | ios::app);

                                        if(add_manga() == 1){
                                            fo.close();
                                            break;
                                        }
                                        else{
                                            cout<<"\n Writing into binary file\n";
                                            fo.write((char*)&ml, sizeof(Manga_list));
                                            fo.close();
                                        }
                                        
                                        
                                        if(!fo.good()){
                                            error("Error occured at the time of writing");
                                            return 1;
                                        }
                                        else if(fo.good()){
                                            success("Data entry sucessful");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;
                                
                                case 2: 
                                        clear();
                                        flag = 0;
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");                                            
                                            return 1;
                                        }
                                        cout<<"\n<----Modify---->";
                                        cout<<"\nEnter the name of the manga to be modified: ";
                                        cin.getline(to_be_updated, 100);

                                            while(fi.read((char*)&ml, sizeof(Manga_list))){
                                               
                                                strcpy(existing_name, ml.manga_name);
                                                strcpy(name_to_check, to_be_updated);

                                                if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
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
                                            if(!fo.good()){
                                                error("Error occured at the time of writing");
                                                return 1;
                                            }
                                            else if(fo.good()){
                                                if(!flag){
                                                    error("Record not found");
                                                    remove("update.dat");
                                                    fi.close();
                                                    break;
                                                }
                                                else
                                                    success("Data updation successful");
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
                                            error("Error occured while opening the file / File does not exist");
                                            break;
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
                                                error("Error occured while opening the file / File does not exist");
                                                break;
                                            } 

                                            delete_manga();

                                            if(!flag){
                                                error("Record not found");
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            else{
                                                success("Manga removed from the list");
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
                                        error("Invalid Command");
                                        break;      
                            }
                        }while(ch != 6);
                        break;
                
                case 3: return 1;
                
                default: 
                        error("Invalid Command");
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

    if(anime_check(name) == 1)
        return 1;
    
    strcpy(al.anime_name, name);
    
    cout<<"\n Have you completed the anime (y/n): ";
    cin>>anime_completed;
    al.completed = anime_completed;
                    
    switch(anime_completed){
        case 'n':   cout<<" Enter the season: ";
                    cin>>anime_season;
                    al.season = anime_season;
                    
                    cout<<" Enter the recent episode watched: ";
                    cin>>ep;
                    al.recent_ep_watched = ep;
                    break;
        case 'y':   cout<<"\n";
                    break;
        default:    error("Enter valid input");
                    return 1;
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
                        cout<<" You have already completed watching the anime, continuing will set anime completed to 'no'";
                        cout<<"\n Do you want to continue? (y/n): ";
                        cin>>y_n;
                        if(y_n == 'y'){
                            al.completed = 'n';
                            cout<<"\n Anime completed status set to 'no'";
                            
                            cout<<"\n Enter the season: ";
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
    char to_be_deleted[100], original[100];
    flag = 0;

    cout<<"\n Enter the name of the anime to be deleted: ";
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&al, sizeof(Anime_list))){
            
            strcpy(original, al.anime_name);
            
            if(strcmpi(strip(original), strip(to_be_deleted)) == 0){
                flag = 1;
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
    cin.getline(mng, 100);

    if(manga_check(mng) == 1)
        return 1;
    
    strcpy(ml.manga_name, mng);
    
    cout<<"\n Have you completed reading the manga (y/n): ";
    cin>>fin;
    ml.finished = fin;

    switch(fin){
        case 'n':   cout<<" Enter recent manga chapter read: ";
                    cin>>mng_chap;
                    ml.recent_chap_read = mng_chap;
                    break;
        case 'y':   cout<<"\n";
                    break;
        default:    error("Enter valid input");
                    return 1;
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
                        cout<<" You have already completed reading the manga, continuing will set manga completed to 'no'";
                        cout<<"\n Do you want to continue? (y/n): ";
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
    char to_be_deleted[100], temp[100];
    flag = 0;

    cout<<"\n Enter the name of the manga to be deleted: ";
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&ml, sizeof(Manga_list))){
            
            strcpy(temp, ml.manga_name);

            if(strcmpi(strip(temp), strip(to_be_deleted)) == 0){
                flag = 1;
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

// clears the terminal screen
void clear(){
    cout<<"\x1B[2J\x1B[H";
}

// turns the text color red
void error(string error){
    cout<<"\033[31;1m " + error + "\033[0m";
}

// turns the text color green
void success(string success){
    cout<<"\033[32;1m " + success + "\033[0m";
}

// removes all the spaces in a sentence
char* strip(char *name){
    int i=0, chk, j;
    
    while(name[i]!='\0'){
        chk=0;
        if(name[i]==' '){
            for(j=i; name[j-1]!='\0'; j++)
                name[j] = name[j+1];
            chk = 1;
        }
        if(chk==0)
            i++;
    }
return name;
}

// checks if the anime passed in the argument and the matching original anime is the same case insensitively
int anime_check(char *Aname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("anime.dat", ios::in | ios::binary);
    while(fi.read((char*)&al, sizeof(Anime_list))){

        strcpy(temp1, al.anime_name);
        strcpy(temp2, Aname);

        if(strcmpi(strip(temp1), strip(temp2)) == 0){
            cout<<endl;
            error("Anime already exists");
            fi.close();
            return 1;
        }
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}

// checks if the manga passed in the argument and the matching original manga is the same case insensitively
int manga_check(char *Mname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("manga.dat", ios::in | ios::binary);
    while(fi.read((char*)&ml, sizeof(Manga_list))){

        strcpy(temp1, ml.manga_name);
        strcpy(temp2, Mname);

        if(strcmpi(strip(temp1), strip(temp2)) == 0){
            cout<<endl;
            error("Manga already exists");
            fi.close();
            return 1;
        }
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}
