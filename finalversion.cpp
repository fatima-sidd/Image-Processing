#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<math.h>

using namespace std;
bool saved = false;

#define MaxRows 500
#define MaxCols 500

struct grayImage{

    grayImage(){

        Rows = Cols = 0;
        loaded = false;

        for(int r = 0; r< MaxRows; r++)
            for(int c = 0; c< MaxCols; c++)
                Image[r][c] = 0;
    }

    unsigned short setPixel(unsigned short value, int r, int c){
        if( r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        Image[r][c] = value;
        return value;
    }

    int getPixel(int r, int c){
        if( r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        return Image[r][c];
    }

    int setRows(int rows){
        if(rows < 1 || rows > MaxRows)
            return -1;
        Rows = rows;
        return Rows;
    }

    int getRows(){
        return Rows;
    }

    int setCols(int cols){
        if(cols < 1 || cols > MaxCols)
            return -1;
        Cols = cols;
        return Cols;
    }

    int getCols(){
        return Cols;
    }

    int Save(string File_Name){

        if (loaded=false)
        {
            return 3;
        }

        int n = File_Name.length();
        if (File_Name[n-4]!= '.' || File_Name[n-3]!= 'p'|| File_Name[n-2]!= 'g' || File_Name[n-1]!= 'm' )
        {
            cout<<"Save unsuccessfull"<<endl<<"File name not correct";
            return 1;
        }

            ofstream OUTPUT(File_Name.c_str());

        if (!OUTPUT)
        {
            cout<<"Save unsuccessful"<<endl<<"Unable to create a file";
            return 2;
        }



        OUTPUT<<"P2"<<endl<<"#hackslash"<<endl<<Cols<<" "<<Rows<<" "<<endl<<Maximum<<endl;



        for (int r=0; r<Rows; r++)
        {
            for (int c=0; c<Cols; c++)
            {
                OUTPUT<<Image[r][c]<<" ";
            }

            OUTPUT<<endl;
        }
        OUTPUT.close();
        saved = true;

        if (saved == true)
        {
            cout<<"Saving successful"<<endl<<endl;
        }
        return 0;



    }

    int load(string File_Name){

        int n = File_Name.length();
        if (File_Name[n-4]!= '.' || File_Name[n-3]!= 'p'|| File_Name[n-2]!= 'g' || File_Name[n-1]!= 'm' )
        {
            cout<<"Load unsuccessful" <<endl<<"File name not correct"<<endl<<endl;
            return 1;
        }

        ifstream INPUT(File_Name.c_str());

        if (!INPUT)
        {
            cout<<"Load unsuccessful" <<endl<<"Unable to open a file for reading"<<endl<<endl;
            return 2;
        }


        string MagicNum;
        getline(INPUT, MagicNum);

        if (MagicNum!="P2")
        {
            INPUT.close();
            cout<<"Load unsuccessful" <<endl<<"Magic Number not correct"<<endl<<endl;
            return 3;
        }

        string Comment;
        getline(INPUT, Comment);

        INPUT>>Cols>>Rows>>Maximum;

        setRows(Rows);
        setCols(Cols);
        Maximum=Maximum;

        for (int r=0; r<Rows; r++)
        {
            for (int c=0; c<Cols; c++)
            {
                INPUT>>Image[r][c];
            }

        }

        INPUT.close();
        loaded=true;
        if (loaded==true)
        {
            cout<<"Load Successful"<<endl<<endl;
        }
        return 0;


    }

    void combineSideBySide(grayImage &Two, int fillValue = 0){
        int L, R, T, B;

         if (Rows<Two.Rows)
        {
            L=0;
            R=Cols;
            T=Rows;
            B=Two.Rows;
        }
        else
        {
            L=Cols;
            R=MaxCols;
            T=Two.Rows;
            B=Rows;
        }

        Fill(L, R, T, B, fillValue);

        for (int r=0; r<Two.Rows; r++)
        {
            for (int c=0; c<Two.Cols, Cols+c<MaxCols; c++)
            {
                Image[r][c+Cols]=Two.Image[r][c];
            }
        }

        if ((Cols+=Two.Cols)>MaxCols) {Cols=MaxCols;}
        if (Rows<Two.Rows) {Rows=Two.Rows;}
    }

    void combineTopToBottom(grayImage &Two, int fillValue = 0){

        int L, R, T, B;

         if (Cols<Two.Cols)
        {
            L=Cols;
            R=MaxCols;
            T=0;
            B=Rows;
        }
        else
        {
            L=Two.Cols;
            R=MaxCols;
            T=Rows;
            B=Rows+Two.Rows;
        }

        Fill(L, R, T, B, fillValue);

      for (int r=0; r<Two.Rows, Rows+r<MaxRows; r++)
        {
            for (int c=0; c<Two.Cols; c++)
            {
                Image[r+Rows][c]=Two.Image[r][c];
            }
        }


        if ((Rows+=Two.Rows)>MaxRows) {Rows=MaxRows;}
        if (Cols<Two.Cols) {Cols=Two.Cols;}


    setRows(Rows);
    setCols(Cols);
    }

    void FadeIn(grayImage& Two, int seconds, int frameRate = 30, string BaseFileName=0){

        grayImage GM;
        double stepsize=1.0/(seconds*frameRate);

        if (Rows < Two.Rows)
        {
            GM.Rows=Two.Rows;
        }
            else
                GM.Rows=Rows;

        if (Cols < Two.Cols)
        {
            GM.Cols=Two.Cols;
        }
            else
                GM.Cols=Cols;

        if (Maximum < Two.Maximum)
        {
            GM.Maximum=Two.Maximum;
        }
            else
                GM.Maximum=Maximum;


        GM.loaded=true;

        int ctr=0;
        for (double alp=1; alp>=0; alp-=stepsize)
        {
            for (int r=0; r<GM.Rows; r++)
            {
                for (int c=0; c<GM.Rows; c++)
                {
                    GM.Image[r][c]= (Image[r][c]*alp) + (1-alp)*(Two.Image[r][c]);

                }
            }


            char N[10];
            itoa(ctr, N, 10);

            GM.Save(BaseFileName + N + ".pgm");

            ctr ++;

            if (0 > alp-stepsize && alp-stepsize> -stepsize )
            {
                alp=0;

            }

        }


    }

    void changeBrightness(int amount){

        for (int R=0; R<Rows; R++)
        {
            for (int C=0; C<Cols; C++)
            {
                Image[R][C]=(Image[R][C]+amount);

                if (Image[R][C]>Maximum)
                {
                    Image[R][C]=Maximum;
                }
            }
        }
    }

    void Flip(int HorizontalOrVertical){

        if (HorizontalOrVertical==1)
            FlipHorizontal();

        else
            FlipVertical();
    }

    void Negative(){
       for (int R=0; R<Rows; R++)
        {
            for (int C=0; C<Cols; C++)
            {
                Image[R][C]=Maximum-Image[R][C];
            }
        }
    }

    void meanFilter(grayImage& Result, int filtersize=3){


    Result.Rows=Rows;
    Result.Cols=Cols;
    Result.Maximum=Maximum;

    int FS=filtersize/2;

    for (int R=FS; R<Rows-FS; R++)
    {
        for (int C=FS; C<Cols-FS; C++)
        {
            int sum=0;

            for(int i = R-FS ; i <= R+FS ; i++)
            {
                for(int j = C-FS ; j<=C+FS ; j++)
                {
                    sum+=Image[i][j] ;
                }
            }

            int avg = 0;
            avg=sum/(filtersize*filtersize);
            Result.Image[R][C]= avg ;
        }
    }
}

    void medianFilter(grayImage& Result, int filterSize = 3){

    Result.Rows=Rows;
    Result.Cols=Cols;
    Result.Maximum=Maximum;

    int TC=(filterSize*filterSize);
    int FS=filterSize/2;
    int i = 0 ;
    int A[TC] ;

    for (int R=FS; R<Rows-FS; R++)
    {
        for (int C=FS; C<Cols-FS; C++)
        {
            for(int k = R-(FS) ; k <= R+(FS) ; k++)
            {
                for(int l = C-(FS) ; l<=C+(FS) ; l++ , i ++)
                {
                    A[i] = Image[k][l] ;
                }
            }
        Selection_sort(A, TC);
        i = 0 ;
        Result.Image[R][C]=A[TC/2];
        }

    }
}

    void Resize(grayImage& Result, int NewRows, int NewColumns){

        if (NewRows<0 || NewColumns<0)
            return;

        if (NewColumns>MaxCols)
            NewColumns=MaxCols;

        if (NewRows>MaxRows)
            NewRows=MaxRows;

        double C=NewColumns;
        C = C/Cols;

        double R=NewColumns;
        R =R/Rows;



        for (int roww=0; roww<NewRows; roww++)
        {
            for (int coll=0; coll<NewColumns; coll++)
            {
                double ROWW, COLL;
                ROWW = roww / R ;
                COLL = coll / C ;
                int NEW_R, NEW_C;
                NEW_R = ROWW;
                NEW_C = COLL;

                Result.Image[roww][coll] = ((ROWW-NEW_R)*Image[NEW_R][NEW_C]) + ((NEW_R + 1 -ROWW)*Image[NEW_R][NEW_C])   ;
            }
        }

        Result.Rows=NewRows;
        Result.Cols=NewColumns;
        Result.Maximum=Maximum;
    }

    void Resize(grayImage& Result, double Ratio){

    int NewRows; int NewColumns;
    NewRows=Ratio*Rows;
    NewColumns=Ratio*Cols;

    Resize(Result, NewRows, NewColumns);
    }

    void Quantize(int Levels){

    int siz;
    siz=Maximum/Levels;


    for (int i=0; i<Maximum; i+=siz)
    {
        for (int R=0; R<Rows; R++)
        {
            for (int C=0; C<Cols; C++)
            {
                if (Image[R][C] >= i && Image[R][C] < (i+siz))
                {
                    int avg=0;
                    avg=(i+i+siz)/2;
                    Image[R][C]=avg;
                }

            }
        }
    }
}

    void RotateR(grayImage& Result ,double angle, int aboutx=0 , int abouty=0){

        if (aboutx>Rows || abouty>Cols)
        {
            return;
        }

    	int R,C;
    	angle = (3.141592*angle)/180.0;

    		for(int i=0;i<Rows;i++){
	    	    for(int j=0;j<Cols;j++){

	    	    	R=((i-aboutx)*cos(angle)+(j-abouty)*sin(angle))+aboutx;
	    	     	C=(-(i-aboutx)*sin(angle)+(j-abouty)*cos(angle))+abouty;

	    	     	if(R>0 && C>0 && R<Rows && C<Cols)
                    {
                        Result.Image[i][j]= (Image[R][C] +Image[R+1][C]+Image[R][C+1] + Image[R+1][C+1] )/4;
                    }

	    	    }
	    	}
    	    Result.Rows= Rows;
			Result.Cols=Cols;
			Result.Maximum=Maximum;

	}

    void Transform(grayImage& Result, double Matrix[3][3]){

    double i,j,z;

    for (int r=0; r<Rows; r++)
    {
        for (int c=0; c<Cols; c++)
        {
            z = ( (r*Matrix[2][0]) + (c*Matrix [2][1]) + (Matrix[2][2]) );
            i = ( (r*Matrix[0][0]) + (c*Matrix [0][1]) + (Matrix[0][2]) )/z;
            j = ( (r*Matrix[1][0]) + (c*Matrix [1][1]) + (Matrix[1][2]) )/z;

            int new_rows=i;
            int new_cols=j;

            if (z!=0 && new_rows>0 && new_rows<MaxRows && new_cols>0 && new_cols<MaxCols)
            {
                Result.Image[new_rows][new_cols] = Image[r][c];
            }
        }
    }
    Result.Rows = Rows ;
    Result.Cols = Cols ;
    Result.Maximum = Maximum ;
}

    void Crop(grayImage& Result, int L, int T, int R, int B){

    if (B<T || R<L || R>Cols || B > Rows || L> Cols || T> Rows)
    {
       return;
    }

    Result.Rows=B-T;
    Result.Cols=R-L;

    for (int r=0, i=T; r<=Result.Rows, i<=B; r++, i++)
    {
        for (int c=0, j=L; c<=Result.Cols, j<=R; c++, j++)
        {
            Result.Image[r][c]=Image[i][j];
        }
    }

    Result.Maximum=Maximum;
}

    void Filter(grayImage& Result, double Mask[3][3]){

    int FS=3/2;
        for (int R=FS; R<Rows-FS; R++)
        {
            for (int C=FS; C<Cols-FS; C++)
            {
                int sum=0;

                 for(int i = R-FS, k = 0 ; i <= R+FS ; k++, i++)
                 {
                   for(int j = C-FS, l = 0; j<=C+FS ; l++, j++)
                   {

                       sum+=Image[i][j] *Mask[k][l];

                   }
                  Result.Image[R][C] = sum;
    		}
		}
             Result.Maximum = Maximum;
		     Result.Rows = Rows;
             Result.Cols = Cols;

       }
    }

    void Derivative(grayImage&Result, int Mask1[3][3],int Mask2[3][3]){

    int v1=0, v2=0;

     for(int i=1;i<Rows-1;i++)
     {
     	for(int j=1;j<Cols-1;j++)
    	{
	     	int id = i- 3/2;
	     	int jd = j- 3/2;
     		for(int m1=0; m1<3; m1++)
            {
     			for(int m2=0; m2<3; m2++)
     			{
     		 		v1+=(Image[id + m1][jd + m2] * Mask1[m1][m2]);
     		 		v2=(Image[id + m1][jd + m2] * Mask2[m1][m2]);
     		 	}
     		}

        	Result.Image[i][j]=sqrt((v1*v1)+(v2*v2));
            v1=0;
            v2=0;
		}

	 }
	        Result.Rows= Rows;
			Result.Cols=Cols;
			Result.Maximum=Maximum;
			Result.loaded=true;
    }

private:
    void Selection_sort(int A[], int n){

    int min;
    for (int i=0; i<n; i++)
    {
        min=A[i];
        for (int j=i+1; j<n; j++)
        {
            if (A[j]<A[i])
            {
                int temp;
                temp=A[j];
                A[j]=A[i];
                A[i]=temp;
            }
        }
    }
}

    void FlipHorizontal(){

    int temp;
    for (int i=0; i<Rows; i++)
    {
        for (int j=0; j<Cols/2; j++)
        {
            temp=Image[i][j];
            Image[i][j]=Image[i][Cols-j];
            Image[i][Cols-j]=temp;

        }
    }
    }

    void FlipVertical(){

    int temp;
    for (int i=0; i<=Rows/2; i++)
    {
        for (int j=0; j<=Cols; j++)
        {
            temp=Image[i][j];
            Image[i][j]=Image[Rows-i][j];
            Image[Rows-i][j]=temp;

        }
    }
}

    void Fill(int L, int R, int T, int B, int fillval){
        for (int i=T; i<B; i++)
        {
            for (int j=L; j<R; j++)

                Image[i][j]=fillval;
        }
    }

    unsigned short Image[MaxRows][MaxCols];
    int Rows, Cols, Maximum;
    bool loaded;
};

int main(){

    grayImage GM1, GM2, New1;

    string file_name1, file_name2;
    int opt=1;

    cout<<"Welcome!"<<endl;
            cout<<endl<<endl<<"Enter 0 to exit program"<<endl<<endl
            <<"What do you want to do?"<<endl
            <<"1. Combine Side by Side "<<endl
            <<"2. Combine Top to Bottom " <<endl
            <<"3. Fade In "<<endl
            <<"4. Change Brightness " <<endl
            <<"5. Flip " <<endl
            <<"6. Negative " <<endl
            <<"7. Mean Filter " <<endl
            <<"8. Median Filter " <<endl
            <<"9. Resize by Number of Rows and Columns " <<endl
            <<"10. Resize by Ratio " <<endl
            <<"11. Quantize " <<endl
            <<"12. Rotate "<<endl
            <<"13. Transform "<<endl
            <<"14. Crop "<<endl
            <<"15. Filter "<<endl
            <<"16. Derivative " <<endl;

        cout<<endl<<"Option no:  ";
        cin>>opt;

    while (opt!=0)
    {


        cout<<"Enter the name of the pgm file to be loaded"<<endl;

        cin>>file_name1;

        cout<<endl<<"Loading the file..."<<endl;

        GM1.load(file_name1);

        while (opt<0 || opt>16)
        {
            cout<<endl<<"Error"<<endl
            <<"Please Enter correct option number"<<endl
            <<"Option no:  ";
            cin>>opt;
            cout<<endl;
        }

        if (opt == 1 || opt == 2 || opt == 3)
        {
            cout<<"You need another pgm file to perform this function"<<endl
                <<"Enter the name of the second pgm file"<<endl;
            cin>>file_name2;

            cout<<endl<<"Loading the file..."<<endl;

            GM2.load(file_name2);

        }

        if (opt==1)
        {
            cout<<"COMBINING SIDE BY SIDE"<<endl<<endl
            <<"Enter the Fill-in Value (Between 0 and 255)"<<endl;
            int fill_val;
            cout<<"Fill-in Value:  ";
            cin>>fill_val;


            while (fill_val<0 || fill_val>255)
            {
                cout<<endl<<"Error"<<endl
                <<"Enter a valid fill-in Value"<<endl
                <<"Fill-in Value:  ";
                cin>>fill_val;
            }
            cout<<endl<<endl

            <<"Which file do you want on left (1 or 2)?"<<endl
            <<"1. "<<file_name1<<endl
            <<"2. "<<file_name2;

            int left;
            cout<<endl<<"Option no:  ";
            cin>>left;

            while (left != 1 && left != 2)
            {
                cout<<endl<<"Error" << endl
                <<"Please enter correct option"<<endl
                <<"Option no:  ";
                cin>>left;
            }

            cout<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            if (left == 1)
            {
                GM1.combineSideBySide(GM2, fill_val);
                GM1.Save(save_name);
            }

            if (left == 2)
            {
                GM2.combineSideBySide(GM1, fill_val);
                GM2.Save(save_name);
            }

        }

        if (opt==2)
        {
            cout<<"COMBINING TOP TO BOTTOM"<<endl<<endl
            <<"Enter the Fill-in Value (Between 0 and 255)"<<endl;
            int fill_val;
            cout<<"Fill-in Value:  ";
            cin>>fill_val;


            while (fill_val<0 || fill_val>255)
            {
                cout<<endl<<"Error"<<endl
                <<"Enter a valid fill-in Value"<<endl
                <<"Fill-in Value:  ";
                cin>>fill_val;
            }
            cout<<endl<<endl

            <<"Which file do you want on Top (1 or 2)?"<<endl
            <<"1. "<<file_name1<<endl
            <<"2. "<<file_name2<<endl;

            int top;
            cout<<"Option no:  ";
            cin>>top;

            while (top != 1 && top != 2)
            {
                cout<<endl<<"Error" << endl
                <<"Please enter correct option"<<endl
                <<"Option no:  ";
                cin>>top;
            }

            cout<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<endl<<"Saving the file..."<<endl;

            if (top == 1)
            {
                GM1.combineTopToBottom(GM2, fill_val);
                GM1.Save(save_name);
            }

            if (top == 2)
            {
                GM2.combineTopToBottom(GM1, fill_val);
                GM2.Save(save_name);
            }
        }

        if (opt==3)
        {
            int  sec, FR;
            string base_name;
            cout<<"FADE IN"<<endl
                <<"Please enter the the number of seconds"<<endl
                <<"Seconds:  ";

            cin>>sec;



            cout<<endl
                <<"Please enter the frame rate"<<endl
                <<"Frame Rate:  ";

            cin>>FR;

            cout<<endl<<endl<<"Please create a folder named 'Fadein' "<<endl
            <<"Create another folder named 'Fatima2' in it"<<endl
            <<"Then enter any digit to proceed"<<endl;

            int x;
            cin>>x;


            cout<<endl<<endl<<"Which file do you want to see first? (1 or 2)"<<endl
            <<"1. "<<file_name1<<endl
            <<"2. "<<file_name2<<endl;

            int first;

            cout<<"Option no:  ";
            cin>>first;

            while (first != 1 && first != 2)
            {
                cout<<endl<<"Error" << endl
                <<"Please enter correct option"<<endl
                <<"Option no:  ";
                cin>>first;
            }


            if (first==1)
            {

                GM1.FadeIn(GM2,sec,FR,"Fadein\\Fatima2\\");

            }

            if (first == 2)
            {
                GM2.FadeIn(GM1,sec,FR,"Fadein\\Fatima2\\");
            }

        }

        if (opt==4)
        {
            cout<<"CHANGE BRIGHTNESS"<<endl
                <<"Please enter the amount by which brightness is to be changed"<<endl;
            int n;
            cin>>n;

            cout<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.changeBrightness(n);
            GM1.Save(save_name);
        }

        if (opt==5)
        {
            cout<<"FLIP"<<endl
                <<"How do you want to flip this file?"<<endl
                <<"1. Horizontal"<<endl
                <<"2. Vertical"<<endl<<endl;

            int x;

            cout<<"Option no:  ";
            cin>>x;

            while (x != 1 && x!= 2)
            {
                cout<<endl<<"Error" << endl
                <<"Please enter correct option"<<endl
                <<"Option no:  ";
                cin>>x;
            }

            cout<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Flip(x);
            GM1.Save(save_name);

        }

        if (opt==6)
        {
            cout<<"NEGATIVE"<<endl
            <<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Negative();
            GM1.Save(save_name);
        }

        if (opt==7)
        {
            int x;
            cout<<"MEAN FILTER"<<endl<<endl
                <<"Enter the filter size"<<endl
                <<"Filter size:  ";

            cin>>x;

            cout<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.meanFilter(New1, x);
            New1.Save(save_name);

        }

        if (opt==8)
        {
        int x;
            cout<<"MEDIAN FILTER"<<endl<<endl
                <<"Enter the filter size"<<endl
                <<"Filter size:  ";

            cin>>x;

            cout<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.medianFilter(New1, x);
            New1.Save(save_name);

        }

        if (opt==9)
        {
        cout<<"RESIZE BY NUMBER OF ROWS AND COLUMNS"<<endl<<endl
            <<"Enter the new number of rows"<<endl
            <<"New Rows:  ";

        int new_r;
        cin>>new_r;

        while (new_r<0 || new_r>MaxRows)
        {
            cout<<endl<<"Error"<<endl
            <<"Please Enter correct number of rows"<<endl
            <<"New Rows:  ";
            cin>>new_r;
        }
        cout<<endl;

        cout<<endl<<"Enter the new number of columns"<<endl
            <<"New Columns:  ";

        int new_c;
        cin>>new_c;

        while (new_c<0 || new_c>MaxCols)
        {
            cout<<endl<<"Error"<<endl
            <<"Please Enter correct number of columns "<<endl
            <<"New Cols:  ";
            cin>>new_c;
        }
        cout<<endl;

        cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
        string save_name;
        cin>>save_name;

        cout<<"Saving file..."<<endl;

        GM1.Resize(New1, new_r, new_c);
        New1.Save(save_name);

        }

        if (opt==10)
        {
            cout<<"RESIZE BY RATIO"<<endl<<endl
                <<"Enter the ratio you want to resize this as";
            double ratio;
            cin>>ratio;

            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Resize(New1, ratio);
            New1.Save(save_name);
        }

        if (opt==11)
        {
            cout<<"QUANTIZE"<<endl<<endl
                <<"Enter the number of levels (1-255)"<<endl
                <<"Levels:  ";

            int levels;
            cin>>levels;

        while (levels<1 || levels>255)
        {
            cout<<endl<<"Error"<<endl
            <<"Please Enter correct number of levels"<<endl
            <<"Levels:  ";
            cin>>levels;
        }


        cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
        string save_name;
        cin>>save_name;

        cout<<"Saving file..."<<endl;

        GM1.Quantize(levels);
        GM1.Save(save_name);

        }

        if (opt==12)
        {
            double angle;
            int x, y;

            cout<<"ROTATE"<<endl<<endl<<endl
                <<"Enter the angle you want to rotate the picture"<<endl
                <<"Angle:  ";

            cin>>angle;

            cout<<"How much do you want it about x?"<<endl
                <<"About x:  ";

            cin>>x;

            cout<<endl<<endl<<"How much do you want it about y?"<<endl
                <<"About y:  ";

            cin>>y;

            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.RotateR(New1, angle, x, y);
            New1.Save(save_name);
        }

        if (opt==13)
        {
            cout<<"TRANSFORM"<<endl
            <<endl<<"Enter the values of the 3x3 matrix"<<endl;

            double M [3][3];

            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    cin>>M[i][j];
                }
            }


            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Transform(New1, M);
            New1.Save(save_name);

        }

        if (opt==14)
        {
            int L,R,T,B;

            cout<<"CROP"<<endl<<endl
                <<"Enter the following values:  "<<endl
                <<"Left:  ";
            cin>>L;
            cout<<"Right:  ";
            cin>>R;
            cout<<"Top:  ";
            cin>>T;
            cout<<"Bottom:  ";
            cin>>B;

            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Crop(New1, L,T,R,B);
            New1.Save(save_name);
        }

        if (opt==15)
        {

        cout<<"FILTER"<<endl
        <<endl<<"Enter the values of the 3x3 mask"<<endl;

            double M [3][3];

            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    cin>>M[i][j];
                }
            }

            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Filter(New1, M);
            New1.Save(save_name);

        }

        if (opt==16)
        {

            cout<<"DERIVATIVE IMAGE"<<endl
            <<"Enter the values of the first 3x3 mask"<<endl;

            int M1 [3][3];

            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    cin>>M1[i][j];
                }
            }

            cout<<endl<<endl<<"Enter the values of the second 3x3 mask"<<endl;

            int M2 [3][3];

            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    cin>>M2[i][j];
                }
            }

            cout<<endl<<endl<<"Enter the name of the file you want to save this as"<<endl;
            string save_name;
            cin>>save_name;

            cout<<"Saving file..."<<endl;

            GM1.Derivative(New1, M1, M2);
            New1.Save(save_name);
        }

        cout<<endl<<endl<<"Enter 0 to exit program"<<endl<<endl
            <<"What do you want to do?"<<endl
            <<"1. Combine Side by Side "<<endl
            <<"2. Combine Top to Bottom " <<endl
            <<"3. Fade In "<<endl
            <<"4. Change Brightness " <<endl
            <<"5. Flip " <<endl
            <<"6. Negative " <<endl
            <<"7. Mean Filter " <<endl
            <<"8. Median Filter " <<endl
            <<"9. Resize by Number of Rows and Columns " <<endl
            <<"10. Resize by Ratio " <<endl
            <<"11. Quantize " <<endl
            <<"12. Rotate "<<endl
            <<"13. Transform "<<endl
            <<"14. Crop "<<endl
            <<"15. Filter "<<endl
            <<"16. Derivative " <<endl;

        cout<<endl<<"Option no:  ";
        cin>>opt;
    }

    return 0;
}
