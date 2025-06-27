// Made by Tuna Aydın 
// Can only work for the file format rank/rating/title/votes
// Movie list file name must be imdb_list.txt 
// This the version that doesnt have system("clear");
// Instead there are printf("\n\n); to help with readability
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

//Structure of the movie
typedef struct movie
{
    int rank;
    double rating;
    char title[100];
    int vote;
}imdb;

// Global variables and prototypes
imdb movieList[500];
int movie_amount = 0;
int read_flag = 0;
void menu();
void readData(imdb arr[]);
void findMovie(imdb arr[]);
void sortMovies(imdb arr[]);
void copystruct(imdb *temp, imdb arr);
void insertMovie(imdb arr[]);
void printList(imdb arr[]);
void outFile();

// Main function to start the program immidietly directs to menu
int main()
{
    printf("\n");
    menu();
}

// The menu where we pick what we want to do
// Every function will return here when their process is finished
// Unless the function have a problem and has to exit the program
void menu()
{
    int c;
    
    printf("Choose 1,2,3,4,5,6,7:\n1.Read  movies Data\n2.Find Movie\n3.Insert Movie\n4.List All Movies\n5.Sort Movies\n6.See The Output File\n7.Exit\n");
    scanf("%d", &c);
    getchar();
    // Switch function that leads to the functions
    // If there is not a file readed, it will send the program to the readData automatically
    switch(c)
    {
        case 1:  printf("\n\n");
                    readData(movieList);
                    break;
     
           case 2: if(read_flag)
                    {
                        printf("\n\n");
                        findMovie(movieList);
                    }
                    else
                    {
                         printf("\n\n");
                         printf("There is no file readed for now. \nPlease read the file first\n");
                         readData(movieList);
                    }
                     break;
        case 3: if(read_flag)
                     {
                         printf("\n\n");
                         insertMovie(movieList);
                     }
                       else
                    {
                         printf("\n\n");
                         printf("There is no file readed for now. \nPlease read the file first\n");
                         readData(movieList);
                    } 
                    break;
        
        case 4: if(read_flag)
                    {
                        printf("\n\n");
                        printList(movieList);
                    }
                      else
                    {
                         printf("\n\n");
                         printf("There is no file readed for now. \nPlease read the file first\n");
                         readData(movieList);
                    } 
                    break;
        
        case 5: if(read_flag)
                    {
                        printf("\n\n");
                        sortMovies(movieList);
                        // Sorts movies according to their votes and prints them
                        for(int i = 0; i < movie_amount; i++)
                        {
                            printf("%d/%.1lf/%s/%d\n",  movieList[i].rank, movieList[i].rating, movieList[i].title,  movieList[i].vote);
                        }
                    }
                     else
                    {
                         printf("\n\n");
                         printf("There is no file readed for now. \nPlease read the file first\n");
                         readData(movieList);
                    } 
                    break;
        case  6:
                    outFile();
                     break;
        case 7: printf("Exiting now...");
                    exit(0); 
                    break;
        
        default: printf("\n\n"); printf("Invalid input try again.\n");
                     menu();
    }
    menu();
}

// The function that reads the file into the array
void readData(imdb arr[])
{
    char buffer[300];
    char * token;
    FILE *fp;
    fp = fopen("imdb_list.txt", "r");
    if(fp == NULL)
    {
        // EXits program in the case of a problem
        printf("Error opening file. There is not a file named imdbtop250.txt or it is inaccesible. Exiting program.");
        exit(1);
    }
    int i = 0;
    // Divides the whole string into tokens and places the values accordingly in their structs
    while(fgets(buffer, 300, fp) != NULL)
    {
        token = strtok(buffer, "/");
        arr[i].rank = atoi(token);
        token = strtok(NULL, "/");
        arr[i].rating = atof(token);
        token = strtok(NULL, "/");
        strcpy(arr[i].title, token);
        token = strtok(NULL, "/");
        arr[i].vote = atoi(token);
        i++;
    }
    movie_amount = i;
    fclose(fp);
    read_flag = 1;
    printf("File has been successfully readed.\n");
}
// Finds the movies you want according to the year
// And puts them into a file called output.txt
void findMovie(imdb arr[])
{
    int yearz, year, succes = 0;
    char* token;
    FILE *fp;
    fp = fopen("output.txt", "w");
    
    printf("Please enter the year you are looking for: ");
    scanf("%d", &yearz);
    
    for(int i = 0; i < movie_amount ;i++)
    {
        // Since our title format is movietitle(year) we have to seperate the number from () 
        token = strchr(arr[i].title , '(');
        if(token != NULL)
        {
            year = atoi(token + 1);
            if(yearz == year)
            {
                printf("%s\n", arr[i].title);

                fprintf(fp, "%d/%.1lf/%s/%d\n", arr[i].rank, arr[i].rating, arr[i].title,  arr[i].vote);
                succes++;
            }
        }
    }
    printf("\n\n");
    if(succes != 0)
    {
        printf("Matched dates data have been putted into output.txt\n");
    }
    else
    {
        printf("Could not find any matching dates\n");
    }
    fclose(fp);
}

// Uses bubble sort to sort the movies according to their votes
void sortMovies(imdb arr[])
{
    imdb temp;
    for(int i = 0; i  < movie_amount - 1; i++)
    {
        for(int j = 0; j < movie_amount - 1 - i; j++)
        {
            if(arr[j].vote < arr[j+1].vote)
            {
                copystruct(&temp, arr[j]);
                copystruct(&arr[j], arr[j+1]);
                copystruct(&arr[j+1], temp);
            }
        }
    }
}

// Copies a struct into another
void copystruct(imdb *temp, imdb arr)
{
    temp->rating = arr.rating;
    strcpy(temp->title, arr.title);
    temp->vote = arr.vote;
}

// Insert in a movie and shifting all of the others rank
void insertMovie(imdb arr[])
{
    if(movie_amount >= 499)
    {
        printf("Not enough space to put another movie...Exiting the sytem.");
        exit(499);
    }
    // Inserting movies name
    imdb newMovie;
    int year, flag = 0, secondFlag = 0;
    char buffer[6];
    
    printf("Name of the Movie: ");
    fgets(newMovie.title, 93, stdin);
    newMovie.title[strcspn(newMovie.title, "\n")] = '\0';
    
    printf("Year of the movie: ");
    scanf("%d", &year);
    getchar();
    // Constructing the year according to the format
    sprintf(buffer, "(%d)", year);
    strcat(newMovie.title, buffer);
    
    // Check if movie already exists
    for(int i = 0; i < movie_amount ;i++)
    {
        if (strcasecmp(newMovie.title, arr[i].title) == 0)
        {
            printf("This movie already exists. Returning To the menu...\n");
            flag = 1;
            return;
        }
    }
    // If the movie doesnt exist in the list add it to its proper place
    // Place it according to its rating
    if(!flag)
    {
        // Input rating
        printf("Rating of The Movie: ");
        do
        {
            scanf("%lf", &newMovie.rating);
            getchar();
            if(newMovie.rating < 0.0 || newMovie.rating > 10.0)
            {
                printf("Rating must be between 0.0 and 10.0. Please inout accordingly.");
            }
        }while(newMovie.rating < 0.0 || newMovie.rating > 10.0);
        // Input votes
        printf("Votes of the new Movie: ");
        scanf("%d", &newMovie.vote);
        getchar();
        // Checks if the new movie has higher rating than the ones on the list
        // If not adds it to the end of the list
        // If it is, shifts the lower ones to the current end of the list(Not the end of the whole array)
        for(int i = 0; i < movie_amount; i++)
        {
            if(newMovie.rating  > arr[i].rating)
            {
                newMovie.rank = arr[i].rank;
                for(int j = movie_amount - 1; j >= i; j--)
                {
                    copystruct(&arr[j + 1], arr[j]);
                }
                arr[movie_amount].rank = movie_amount + 1;
                // Copies the new movie to its proper place
                copystruct(&arr[i], newMovie);
                secondFlag = 1;
                break;
            }
        }
        // Adds new movie to the end of the list if it is lower
        if(secondFlag == 0)
        {
            newMovie.rank = movie_amount + 1;
            copystruct(&arr[movie_amount], newMovie);
            arr[movie_amount].rank = newMovie.rank;
        }
        movie_amount++;
    }
    // Outputs the new list and updates the file
    printf("\n\n");
    FILE *fp;
    fp = fopen("imdb_list.txt", "w");
    for(int i =  0; i < movie_amount; i++)
    {
        fprintf(fp, "%d/%.1lf/%s/%d\n", arr[i].rank, arr[i].rating, arr[i].title,  arr[i].vote);
    }
    fclose(fp);
    printf("File has been updated with the new movie...\n");
}
// Prints the movie list
void printList(imdb arr[])
{
    printf("List of the movies are...\n");
    for(int i = 0; i < movie_amount; i++)
    {
        printf("%d/%.1lf/%s/%d\n", arr[i].rank, arr[i].rating, arr[i].title,  arr[i].vote);
    }
}
// Prints the output.txt
void outFile()
{
    char buffer[500];
    FILE *fp;
    fp = fopen("output.txt", "r");
    if(fp == NULL)
    {
        printf("Output.txt does'nt exists or it could'nt been opened.\n");
        return;
    }
    
    printf("\n");
    while(fgets(buffer, 500, fp) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
}
