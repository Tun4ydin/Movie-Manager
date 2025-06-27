# Movie-Manager
This is a Movie manager terminal program
Can only be used with a file that is called imdb_list.txt and the file must have a rank/rating/title/votes string format any other format will cause problems
!!There will be two versions If you only see one thats called MovieManager.c that will have system("clear"); calls that are not compatible with Windows OS.!!
!!I will upload a file called MovieManager_nosys.c that doesnt have any system calls.!!
You may have problems if you already have a file called output.txt since this program creates and uses that file for some of its functions

How the program works:
When you compile and run you will see a menu that says:

Choose 1,2,3,4,5,6,7:
1.Read movies Data
2.Find Movie
3.Insert Movie
4.List all Movies
5.Sort Movies
6.See the output file
7.Exit

Read movies data:
Reads the file file into the program

Find Movie:
Finds The movies according the the year the user inputs and puts them into the output.txt file

Insert Movie:
Insert a movie which information given by user

List all Movies:
Prints out the list of the movies

Sort Movies:
Sorts and prints the movies according to their votes

See the output file:
prints output.txt

Exit:
Exits the program
