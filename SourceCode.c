#include <stdio.h>
#include <string.h>
#include <dirent.h>

int equal_string(char *x, char *y){
	int i=0;
	while(*(x+i)!='\0'){
		if(*(x+i)!=*(y+i)){
			return 0;
		}
		i++;
	}
	if(*(y+i)!='\0'){
		return 0;
	}
	return 1;
}

void main(){
	DIR* datafile=opendir("Data");
	if(datafile){
		closedir(datafile);
	}
	else{
		mkdir("Data");
	}
	
	char input1[100];
	printf("Welcome to MiniDB Manager!\n");
	Start:
	printf(">>>");
	scanf("%s",input1);
	
	if(equal_string(input1,"create")){
		scanf("%s",input1);

		if(equal_string(input1,"database")){
			scanf("%s",input1);
			
			char location[]="Data/";
			strcat(location,input1);
			DIR* datafile=opendir(location);
			
			if(datafile){
				closedir(datafile);
				printf("Database already exists.\n");
				fflush(stdin);
				goto Start;
			}
			else{
				mkdir(location);
				printf("Database created.\n");
				fflush(stdin);
				goto Start;
			}
			
		}
		else if(equal_string(input1,"table")){
			scanf("%s",input1);
			char database[]="Data/";
			strcat(database,input1);
			
			DIR* loc=opendir(database);
			
			if(loc){
				closedir(loc);
				scanf("%s",input1);
				char sample_loc[100];
				strcpy(sample_loc,database);
				strcat(sample_loc,"/");
				strcat(sample_loc,input1);
				strcat(sample_loc,".csv");
				
				FILE* check_table;
				if(check_table=fopen(sample_loc,"r")){
					
					printf("Table already exists.\n");
					fclose(check_table);
					fflush(stdin);
					goto Start;
				}
				else{
					FILE* table_in_use=fopen(sample_loc,"w");
					
					scanf("%s",input1);
					if(equal_string(input1,"(")){
						scanf("%s",input1);
						
						char table_struct_heading[10000];
						int table_struct_heading_size=0;
						
						while(!equal_string(input1,")")){
							char column[100];
							strcpy(column,input1);
							strcat(column,", ");
							table_struct_heading_size+=strlen(column);
							strcat(table_struct_heading,column);
							scanf("%s",input1);
							column[0]='\0';
						}
						table_struct_heading[table_struct_heading_size-2]='\n';
						table_struct_heading[table_struct_heading_size-1]='\0';
						fputs(table_struct_heading,table_in_use);
						fclose(table_in_use);
						table_struct_heading[0]='\0';
						printf("table created.\n");
						fflush(stdin);
						goto Start;
					}
					
					else{
						char ar[]="Error at '";
						strcat(ar,input1);
						strcat(ar,"', expected ' ( ' .\n");
						fclose(table_in_use);
						remove(sample_loc);
						printf(ar);
						fflush(stdin);
						goto Start;
					}
				}
				
			}
			else{
				printf("Database %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}

		}
		else{
			char ar[]="Error at ";
			strcat(ar,input1);
			strcat(ar,"\n");
			printf(ar);
			fflush(stdin); 
			goto Start;
		}
	}
	else if(equal_string(input1,"show")){
		scanf("%s",input1);
		
		if(equal_string(input1,"databases")){
			printf("\n------------------\n");
			printf("Databases:\n------------------\n");
			DIR* d=opendir("Data");
			struct dirent *dir;
			dir=readdir(d);dir=readdir(d);
			while((dir=readdir(d))!=NULL){
				printf("%s\n",dir->d_name);
			}
			closedir(d);
			printf("------------------\n");
			fflush(stdin);
			goto Start;
		}
		else if(equal_string(input1,"tables")){
			scanf("%s",input1);
			char database[]="Data/";
			strcat(database,input1);
			DIR* loc=opendir(database);
			
			if(loc){
				printf("\n------------------\n");
				printf("%s Tables:\n------------------\n",input1);
				struct dirent *dir;
				dir=readdir(loc);dir=readdir(loc);
				char tablename[20];
				while((dir=readdir(loc))!=NULL){
					strcpy(tablename,dir->d_name);
					int i=0;
					while(tablename[i]!='.'){
						printf("%c",tablename[i]);
						i++;
					}
					printf("\n");
				}
				closedir(loc);
				printf("------------------\n");
				fflush(stdin);
				goto Start;
			}
			else{
				printf("Database %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}
		}
		else{
			char ar[]="Error at ";
			strcat(ar,input1);
			strcat(ar,"\n");
			printf("%s",ar);
			fflush(stdin);
			goto Start;
		}
	}
	else if(equal_string(input1,"view")){
		scanf("%s",input1);
		char database[]="Data/";
		strcat(database,input1);
		DIR* loc=opendir(database);
		
		if(loc){
			scanf("%s",input1);
			strcat(database,"/");
			strcat(database,input1);
			strcat(database,".csv");
			FILE *tabledata=fopen(database,"r");
			if(tabledata){
				char datastring[10000];
				char reader=fgetc(tabledata);
				int i=0;
				while(reader!=EOF){
					datastring[i]=reader;
					i++;
					reader=fgetc(tabledata);
				}
				int j=0;
				int count=0;
				printf("\n------------------------------------------------\n");
				while(i!=j){
					if(datastring[j]==','){
						printf("\t");
						j+=2;
					}
					else if(datastring[j]=='\n'){
						if(count==0){
							printf("\n------------------------------------------------\n");
							count=1;
							j++;
						}
						else{
							printf("\n");
							j++;
							continue;
						}
					}
					else{
						printf("%c",datastring[j]);
						j++;
					}
				}
				printf("------------------------------------------------\n");
				
				fflush(stdin);
				goto Start;
			}
			else{
				printf("Table doesn't exists.\n");
				fflush(stdin);
				goto Start;
			}
		}
		else{
			printf("Database %s doesn't exists.\n",input1);
			fflush(stdin);
			goto Start;
		}
	}
	else if(equal_string(input1,"exit")){
		return;
	}
	else if(equal_string(input1,"drop")){
		scanf("%s",input1);
		
		if(equal_string(input1,"database")){
			scanf("%s",input1);
			char loc[]="Data/";
			strcat(loc,input1);
			
			DIR* dir=opendir(loc);
			if(dir){
				closedir(dir);
				rmdir(loc);
				printf("Database %s removed.\n",input1);
				fflush(stdin);
				goto Start;
			}
			else{
				printf("Database %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}
		}
		else if(equal_string(input1,"table")){
			scanf("%s",input1);
			char loc[]="Data/";
			strcat(loc,input1);
			
			DIR* dir=opendir(loc);
			if(dir){
				scanf("%s",input1);
				closedir(dir);
				strcat(loc,"/");
				strcat(loc,input1);
				strcat(loc,".csv");
				FILE *filepath=fopen(loc,"r");
				if(filepath){
					fclose(filepath);
					remove(loc);
					printf("Table %s has been removed.\n",input1);
					fflush(stdin);
					goto Start;
				}
				else{
					printf("Table %s doesn't exists.\n",input1);
					fflush(stdin);
					goto Start;
				}
			}
			else{
				printf("Database %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}
		}
		else{
			printf("Error at %s.\n",input1);
			fflush(stdin);
			goto Start;
		}
	}
	else if(equal_string(input1,"insert")){
		scanf("%s",input1);
		char loc[]="Data/";
			strcat(loc,input1);
			
			DIR* dir=opendir(loc);
			if(dir){
				scanf("%s",input1);
				strcat(loc,"/");
				strcat(loc,input1);
				strcat(loc,".csv");
				FILE *filepath=fopen(loc,"r");
				if(filepath){
					int count=1;
					char reader=fgetc(filepath);
					while(reader!='\n'){
						if(reader==','){
							count+=1;
							reader=fgetc(filepath);
						}
						reader=fgetc(filepath);
					}
					fclose(filepath);
					char mainstring[10000];
					int i=0;
					FILE *filepath=fopen(loc,"r");
					reader=fgetc(filepath);
					while(reader!=EOF){
						mainstring[i]=reader;
						reader=fgetc(filepath);
						i++;
					}
					int j=i;
					for(j; j<count+i; j++){
						scanf("%s",input1);
						strcat(mainstring,input1);
						if(i!=count-1){
							strcat(mainstring,", ");
						}
					}
					strcat(mainstring,"\n");
					FILE *filedest=fopen(loc,"w");
					fputs(mainstring,filedest);
					fclose(filedest);
					printf("Data Added!\n");
					fflush(stdin);
					goto Start;
				}
				else{
					printf("Table %s doesn't exists.\n",input1);
					fflush(stdin);
					goto Start;
				}
			}
			else{
				printf("Database %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}
	}
	else if(equal_string(input1,"delete")){
		scanf("%s",input1);
		char loc[]="Data/";
		strcat(loc,input1);
		
		DIR* dir=opendir(loc);
		if(dir){
			closedir(dir);
			scanf("%s",input1);
			strcat(loc,"/");
			strcat(loc,input1);
			strcat(loc,".csv");
			FILE *filepath=fopen(loc,"r");
			if(filepath){
				int row;
				scanf("%d",&row);
				if(row<=0){
					printf("Invalid row!\n");
					fflush(stdin);
					goto Start;
				}
				char reader;
				char datastring[10000];
				int i=0;
				reader=fgetc(filepath);
				while(reader!=EOF){
					datastring[i]=reader;
					reader=fgetc(filepath);
					i++;
				}
				fclose(filepath);
				datastring[i]='\0';
				int num_of_rows=-1;
				for(int j=0; j<i; j++){
					if(datastring[j]=='\n'){
						num_of_rows++;
					}
				}
				if(num_of_rows<row){
					printf("Row %d doesn't exists in table %s.\n",row,input1);
					fclose(filepath);
					fflush(stdin);
					goto Start;
				}
				char modified_data[10000];
				int num=0;
				FILE *fileloc=fopen(loc,"w");
				i=0;
				int z=0;
				while(datastring[i]!='\0'){
					if(datastring[i]=='\n'){
						num++;
					}
					if(num==row){
						i++;
						while(datastring[i]!='\n'){
							i++;
						}
						num++;
					}
					modified_data[z]=datastring[i];
					i++;
					z++;
				}
				modified_data[z]='\0';
				fputs(modified_data,fileloc);
				printf("Row deleted.\n");
				fclose(fileloc);
				fflush(stdin);
				goto Start;
			}
			else{
				printf("Table %s doesn't exists.\n",input1);
				fflush(stdin);
				goto Start;
			}
		}
		else{
			printf("Database %s doesn't exists.\n",input1);
			fflush(stdin);
			goto Start;
		}
	}
	else{
		printf("Invalid command!\n");
		fflush(stdin);
		goto Start;
	}
}