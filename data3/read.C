std::ifstream filein("name.txt");

for (std::string line; std::getline(filein, line); ) 
{
    std::cout << line << std::endl;
}



void cal(){
char buffer[256];
ifstream inputfile; 
inputfile.open("./twopoints.txt");
ofstream outputfile; 
outputfile.open("./lines.txt");
if(!inputfile){cout << "Unable to open input file";}
if(!outputfile){cout << "Unable to open output file";}

float x1, y1, x2, y2; //改成数组
int i=1;
while (! inputfile.eof() )
  { //判断
    inputfile.getline (buffer,200);  
    sscanf(buffer,"%f %f %f %f",&x1,&y1,&x2,&y2); //八个 %f
    float k=(y2-y1)/(x2-x1);
    float b=y1-k*x1;
    outputfile<<"line"<<i<<"\t"<<"k = "<<k<<"\t"<<"b = "<<b<<endl;
    i++;
  }
inputfile.close();
outputfile.close();
}