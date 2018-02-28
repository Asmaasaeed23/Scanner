#include <iostream>
#include <fstream>

using namespace std;

enum DFAstates{START,INNUM,INID,INASSIGN,INCOMMENT,DONE};
DFAstates state = START;
string Reserved_words[8] = {"if","then","else","end","repeat","until","read","write"};

bool special_symbol(char s_symbol)
{
   return(s_symbol=='+'||'-'||'*'||'/'||'='||'<'||'('||')'||';'||':');
}

bool Letters(char let)
 {
     return (let >= 'A' && let <= 'Z' || let >= 'a' && let <= 'z');
 }

bool Digits(char num)
 {
     return (num >= '0' && num <= '9');
 }
bool Spaces(char space)
{
  return(space==' '||space=='\n');
}
 void tokens(string input){
     int j=0;
     int k=0;
     string tokens_out="";
     while(state != DONE){
        switch(state){

    case START:
        if(Spaces(input[j])){
            tokens_out=" ";
            j++;
        if(j==input.length())
            state=DONE;
        else
            state=START;
        }
         else if (input[j] == '{') {
				j++;
				state = INCOMMENT;
			}
        else if (input[j] == ':') {
				state = INASSIGN;
			}
        else if(Letters(input[j])){
            state=INID;
        }
        else if (Digits(input[j])) {
				state = INNUM;
			}
        else if(special_symbol(input[j])){
                tokens_out+=input[j];
                cout<<input[j]<<" "<<"special symbol"<<endl;
                j++;
                tokens_out=" ";
                if (j == input.length())
                state = DONE;
				else
				state = START;

        }

        else state=DONE;
        break;

    case INID:
        while(Letters(input[j])){
               // if(!Spaces(input[j])){
            tokens_out+=input[j];
            j++;
          //  }
        }
        if(tokens_out=="if"||tokens_out=="read"||tokens_out=="write"||tokens_out=="then"||tokens_out=="until"||tokens_out=="else"||tokens_out=="repeat"){
            cout<<tokens_out<<" "<<"Reserved word"<<endl;}
         else
           {
               cout<<tokens_out<<" "<<"identifier"<<endl;
           }

        tokens_out="";


       // if(tokens_out=="if"||tokens_out=="read"||tokens_out=="write"||tokens_out=="then"||tokens_out=="until"||tokens_out=="else"||tokens_out=="repeat")
            //cout<<tokens_out<<" "<<"Reserved word"<<endl;
       // else if(tokens_out=="if")
           // cout<<tokens_out<<" "<<"Reserved word"<<endl;
        //else if(tokens_out=="write")
         //   cout<<tokens_out<<" "<<"Reserved word"<<endl;
       // else if(tokens_out=="then")
         //   cout<<tokens_out<<" "<<"Reserved word"<<endl;
       // else if(tokens_out=="until")
         //   cout<<tokens_out<<" "<<"Reserved word"<<endl;
       // else if(tokens_out=="else")
       //     cout<<tokens_out<<" "<<"Reserved word"<<endl;
    //    else if(tokens_out=="repeat")
       //     cout<<tokens_out<<" "<<"Reserved word"<<endl;
    //    else
       //     cout<<tokens_out<<" "<<"identifier"<<endl;
//
       // tokens_out=" ";
      /*  for (int j = 0; j <= 8; j++)
			{
				if (Reserved_words[j] == tokens_out)
				k=1;
			}
			if(k==1)

                cout<<tokens_out<<" "<<"Reserved word"<<endl;
            else
                cout<<tokens_out<<" "<<"identifier"<<endl;
            k=0;
            tokens_out=" ";*/
            if (j == input.length())
            state = DONE;
			else
			state = START;

			//tokens_out=" ";

			break;

    case INNUM:
			while (Digits(input[j])) {
				tokens_out+=input[j];
				j++;

			}
			cout << tokens_out << " "<<"number"<<endl;
			tokens_out=" ";
			if (j == input.length())
                state = DONE;
			else
			   state = START;
			break;

    case INCOMMENT:
			if (state == INCOMMENT) {
				while (input[j]!= '}') {
					j++;
				}

				if (j == input.length())
                    state = DONE;
				else
				    state = START;
				j++;
			}
			break;
    case INASSIGN:
			if (input[j] == ':') {
				j += 2;
				cout << ":=" << " "<<"special character"<<endl;
				state = START;
			}
			else {
				if (j == input.length())
                    state = DONE;
				else
				    state = START;
			}
			break;

        }
     }
 }


int main()
{
    ifstream file;
	string lines;
	string complete_code;
	file.open("tiny_sample_code.txt");
	while (!file.eof()) {
		getline(file, lines);
		complete_code += lines;
	}

	freopen("scanner_output.txt", "w", stdout);
	tokens(complete_code);
	fclose(stdout);
	system("pause");

    return 0;
}
