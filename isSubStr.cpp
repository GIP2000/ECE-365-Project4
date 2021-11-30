#include <iostream> 
#include <string>
#include <fstream>

using namespace std;


class SSTR {
    public:
        // checks if s1 and s2 are the merged substring of pss
        // returns the pss string with s1 capatalized and s2 in lowercase if it is a merged substring
        // otherwise it returns *** NOT A MERGE ***
        static string isSSTR(const string& s1, const string &s2, const string& pss){
            if(pss.length() != s1.length() + s2.length()) return errResult; // if the lengths don't match it is an error string
            fill((bool*)matrix,(bool*)matrix+sizeof(matrix)/sizeof(bool),true); // reset the matrix 
            return SSTR::isSSTRRecur(s1,s2,pss,0,0,0); // being the recursion
        }
    
    private:
        static const inline string errResult = "*** NOT A MERGE ***"; 
        static inline bool matrix[1000][1000]; 

        // determines if the strings are merged pss with starting indecies
        // s1->i1
        // s2->i2
        // pss->iss
        // returns the pss string with s1 capatalized and s2 in lowercase if it is a merged substring
        // otherwise it returns *** NOT A MERGE ***
        static string isSSTRRecur(const string& s1, const string &s2, const string& pss, int i1, int i2, int iss){
            string result; 
            for(; iss <pss.length(); iss++){
                if(!matrix[i1][i2]) return errResult; // if we were here already 
                else if(tolower(s1[i1]) != tolower(pss[iss]) && tolower(s2[i2]) != tolower(pss[iss])) { // if we are no good
                    matrix[i1][i2] = false; 
                    return errResult;
                } 
                else if (tolower(s1[i1]) == tolower(s2[i2])){ // if the values are the same
                    // try s1 first
                    string tResult = isSSTRRecur(s1,s2,pss,i1+1,i2,iss+1); 
                    if(tResult != errResult)
                        return result + (char)toupper(pss[iss]) + tResult;
                    matrix[i1+1][i2] = false; // mark that we were already here 
                    
                    //pick s2 if s1 was bad     
                    tResult = isSSTRRecur(s1,s2,pss,i1,i2+1,iss+1); 
                    if(tResult != errResult)
                        return result + (char)tolower(pss[iss]) + tResult;
                    matrix[i1][i2+1] = false; // mark that we were already here 
                    return errResult; 
                }
                else if(tolower(s1[i1]) == tolower(pss[iss])) // if only the first value is the same
                    result += toupper(s1[i1++]); 
                else // if only the second value is the same
                    result += tolower(s2[i2++]);
            }

            return result; 
        }

};


void parseAndOutputFiles(const string& inputFileName, const string& outputfileName){
    ifstream inputFile(inputFileName); 
    ofstream outputFile(outputfileName); 
    if( inputFile.is_open()){
        string s1,s2,s3; 
        while(inputFile >> s1 && inputFile >> s2 && inputFile >> s3){
            string result = SSTR::isSSTR(s1,s2,s3); 
            outputFile << result <<"\n"; 
        }
        
    }
    inputFile.close(); 
    outputFile.close(); 
}




int main(int argc, char** argv){

    if(argc == 4){
        // this was for testing if there are 4 args don't read the file 
        string s1 = argv[1],s2 = argv[2],pss = argv[3];
        string result = SSTR::isSSTR(s1,s2,pss); 
        cout << result<< endl;  
        return 0; 
    } 

    // read the filenames
    string inputfileName,outputfileName; 
    cout << "Enter Input file: "; 
    cin >> inputfileName; 
    cout << "Enter Output file: "; 
    cin >> outputfileName; 

    parseAndOutputFiles(inputfileName,outputfileName); 
    return 0; 
}
