#include <iostream>
#include <string>

using namespace std;

/* compare alpha and numeric segments of two versions */
/* return 1: a is newer than b */
/*        0: a and b are the same version */
/*       -1: b is newer than a */
int rpmvercmp(const char * a, const char * b)
{
    char oldch1, oldch2;
    char * str1, * str2;
    char * one, * two;
    int rc,isnum;

	/* easy comparison to see if versions are identical */
    if (!strcmp(a, b)) return 0;

    str1 = (char*)alloca(strlen(a) + 1);
    str2 = (char*)alloca(strlen(b) + 1);
    strcpy(str1, a);
    strcpy(str2, b);
    one = str1;
    two = str2;

	/* loop through each version segment of str1 and str2 and compare them */
    while (*one && *two) {
        while (*one && !isalnum(*one)) one++;
        while (*two && !isalnum(*two)) two++;

		 /* If we ran to the end of either, we are finished with the loop */
        if (!(*one && *two)) break;

        str1 = one;
        str2 = two;

		/* grab first completely alpha or completely numeric segment */
        /* leave one and two pointing to the start of the alpha or numeric */
        /* segment and walk str1 and str2 to end of segment */
        if (isdigit(*str1)) {
            while (*str1 && isdigit(*str1)) str1++;
            while (*str2 && isdigit(*str2)) str2++;
            isnum = 1;
        } 
        else {
            while (*str1 && isalpha(*str1)) str1++;
            while (*str2 && isalpha(*str2)) str2++;
            isnum = 0;
        }

        oldch1 = *str1;
        *str1 = '\0';
        oldch2 = *str2;
        *str2 = '\0';

        if (one == str1) return -1;     
        if (two == str2) return (isnum ? 1 : -1);

        if (isnum) {
            while (*one == '0') one++;
            while (*two == '0') two++;
            
            if (strlen(one) > strlen(two)) return 1;
            if (strlen(two) > strlen(one)) return -1;
        }

        rc = strcmp(one, two);
        if (rc) return (rc < 1 ? -1 : 1);

        *str1 = oldch1;
        one = str1;
        *str2 = oldch2;
        two = str2;

    }

	/* this catches the case where all numeric and alpha segments have */
    /* compared identically but the segment sepparating characters were */
    if ((!*one) && (!*two)) return 0;

	/* whichever version still has characters left over wins */
    if (!*one) return -1; else return 1;
}

//test
int main(){
    string a = "1.0-1";
    string b = "1.0-2";
    int result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-2 ##" <<result << endl;
    b = "1.0-1";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-1 ##" << result << endl;
    b = "1.0-0";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-0 ##" << result << endl;
    b = "1.0-1a";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-1a ##" << result << endl;
    b = "1.0a-1";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0a-1 ##" << result << endl;
    b = "1.00-1";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.00-1 ##" << result << endl;
    b = "1.0-01";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-01 ##" << result << endl;
    b = "1.0-1.0";
    result = rpmvercmp(a.c_str(),b.c_str());
    cout << "1.0-1.0 ##" << result << endl;
    return 0;
}



















