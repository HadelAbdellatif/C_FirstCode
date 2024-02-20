#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 8
#define tax 0.15
typedef  struct{
    int   e_num ;
    char  name[10];
    float hours;
    float rate;
    float total_salary;
    float tax_amount;
} employee_record;
void calculate(employee_record AR[]){
    for(int i=0;i<len;i++)
    {
    if(AR[i].hours<=40)
    {
        AR[i].total_salary=((AR[i].hours)*(AR[i].rate));
    }
    else
        AR[i].total_salary=((40*AR[i].rate)+((AR[i].hours-40)*(AR[i].rate)*(1.5)));
    }
    for(int j=0;j<len;j++)
    {
        AR[j].tax_amount=AR[j].total_salary*tax;
    }
    }
void sort(employee_record AR[len]){
    employee_record T;
    for (int i=0; i<len; i++)
    for (int j=i+1; j<len; j++)
            if (strcmp(AR[i].name,AR[j].name)>0)
            {
                T = AR[i];
                AR[i] = AR[j];
                AR[j] = T;
            }
}
int main(){
    employee_record AR[len];
    int y;
    char te[99];
    char *token;
    FILE*in = fopen("employees.txt","r");

    for(int i=0;i<len;i++)
        fscanf(in,"%d",&AR[i].e_num);
    fscanf(in,"%d",&y);
    fgets(te,99,in);
    token = strtok(te," ,;");
    for (int i=0;token!=NULL;i++)
    {
        strcpy(AR[i].name,token);
        token=strtok(NULL, " ,;\n");
    }
    for(int i=0;i<len;i++)
        fscanf(in,"%f",&AR[i].hours);
    for(int i=0;i<len;i++)
        fscanf(in,"%f",&AR[i].rate);
    calculate(AR);
    sort(AR);
    FILE*out = fopen("report.txt","w");
    fprintf(out,"Employee Name    Total Salary     Tax Amount     Net Salary\n");
    fprintf(out,"-------------    ------------     ----------     ----------	\n");
    for(int i=0;i<len;i++)
    {
        fprintf(out,"%s               %0.2f               %0.2f       %0.2f      \n",AR[i].name,AR[i].total_salary,AR[i].tax_amount,(AR[i].total_salary-AR[i].tax_amount));
    }
    fclose(out);
  return 0;
}
# C_code
# C_code
