////////////////////////////////////////////////////////////////////////////////
// tiling.cpp - Keenan Crane (kcrane@uiuc.edu)
//
// DESCRIPTION: generates all regular and semi-regular tilings of the plane as
//              Wavefront OBJ files.  Note that the OBJ files generated by this
//              program are fairly sloppy and may include unused vertices.
// USAGE:
//    tiling pattern rows columns out
//
//              pattern - name of the tiling.  Valid names for regular tilings
//                        include "square", "triangle", and "hexagon".  Valid
//                        names for semi-regular tilings are "semi1" through
//                        "semi8".
//
//              rows, columns - roughly the number of generated rows and
//                              columns of vertices. However, many of the
//                              patterns use extra "buffer" rows and columns of
//                              vertices to make face indexing easier, so you
//                              should avoid setting these numbers too low.
//
//              out - output filename (i.e., where the OBJ will be stored)
//
// LICENSE:
//    As the sole author of this code I hereby release it into the public
//    domain.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void printHelp( void );

void generatePattern( string patternName, int rows, int cols, ofstream& out );

void   square( int rows, int cols, ofstream& out );
void triangle( int rows, int cols, ofstream& out );
void  hexagon( int rows, int cols, ofstream& out );
void    semi1( int rows, int cols, ofstream& out );
void    semi2( int rows, int cols, ofstream& out );
void    semi3( int rows, int cols, ofstream& out );
void    semi4( int rows, int cols, ofstream& out );
void    semi5( int rows, int cols, ofstream& out );
void    semi6( int rows, int cols, ofstream& out );
void    semi7( int rows, int cols, ofstream& out );
void    semi8( int rows, int cols, ofstream& out );

// =============================================================================
// =============================================================================
int main( int argc, char **argv )
{
   // check that we have the right number of arguments
   if( argc != 5 )
   {
      // print help if requested
      if( argc >= 2 && string(argv[1]) == "-help" )
      {
         printHelp();
      }
      else // otherwise print usage
      {
         cerr << "usage: " << argv[0] << "pattern rows columns out" << endl;
         cerr << "       (type -help for more options)" << endl;
      }

      exit( 1 );
   }

   // get the size of the pattern
   int rows = atoi( argv[2] );
   int cols = atoi( argv[3] );
   if( rows <= 0 || cols <= 0 )
   {
      cerr << "Error: invalid size ( " << rows << " x " << cols << " )" << endl;
      exit( 1 );
   }

   // open a file for output
   ofstream out( argv[4] );
   if( !out.is_open())
   {
      cerr << "Error: couldn't open file " << argv[4] << " for output." << endl;
      exit( 1 );
   }

   // parse the pattern name and generate the corresponding tiling
   generatePattern( argv[1], rows, cols, out );

   out.close();

   return 0;
}

// =============================================================================
// =============================================================================
void printHelp( void )
{
   cerr << " tiling - Keenan Crane (kcrane@uiuc.edu)                                        "       << endl;
   cerr << "                                                                                "       << endl;
   cerr << " DESCRIPTION: generates all regular and semi-regular tilings of the plane as    "       << endl;
   cerr << "              Wavefront OBJ files.  Note that the OBJ files generated by this   "       << endl;
   cerr << "              program are fairly sloppy and may include unused vertices.        "       << endl;
   cerr << " USAGE:                                                                         "       << endl;
   cerr << "    tiling pattern rows columns out                                             "       << endl;
   cerr << "                                                                                "       << endl;
   cerr << "              pattern - name of the tiling.  Valid names for regular tilings    "       << endl;
   cerr << "                        include \"square\", \"triangle\", and \"hexagon\".  Valid     " << endl;
   cerr << "                        names for semi-regular tilings are \"semi1\" through      "     << endl;
   cerr << "                        \"semi8\".                                                "     << endl;
   cerr << "                                                                                "       << endl;
   cerr << "              rows, columns - roughly the number of generated rows and          "       << endl;
   cerr << "                              columns of vertices. However, many of the         "       << endl;
   cerr << "                              patterns use extra \"buffer\" rows and columns of   "     << endl;
   cerr << "                              vertices to make face indexing easier, so you     "       << endl;
   cerr << "                              should avoid setting these numbers too low.       "       << endl;
   cerr << "                                                                                "       << endl;
   cerr << "              out - output filename (i.e., where the OBJ will be stored)        "       << endl;
   cerr << "                                                                                "       << endl;
   cerr << " LICENSE:                                                                       "       << endl;
   cerr << "    As the sole author of this program I hereby release it into the public      "       << endl;
   cerr << "    domain.                                                                     "       << endl;
   cerr << endl;
}

// =============================================================================
// =============================================================================
void generatePattern( string    patternName,
                      int       rows,
                      int       cols,
                      ofstream& out )
{
   if( patternName == "square"   ) {   square( rows, cols, out ); return; }
   if( patternName == "triangle" ) { triangle( rows, cols, out ); return; }
   if( patternName == "hexagon"  ) {  hexagon( rows, cols, out ); return; }
   if( patternName == "semi1"    ) {    semi1( rows, cols, out ); return; }
   if( patternName == "semi2"    ) {    semi2( rows, cols, out ); return; }
   if( patternName == "semi3"    ) {    semi3( rows, cols, out ); return; }
   if( patternName == "semi4"    ) {    semi4( rows, cols, out ); return; }
   if( patternName == "semi5"    ) {    semi5( rows, cols, out ); return; }
   if( patternName == "semi6"    ) {    semi6( rows, cols, out ); return; }
   if( patternName == "semi7"    ) {    semi7( rows, cols, out ); return; }
   if( patternName == "semi8"    ) {    semi8( rows, cols, out ); return; }

   cerr << "Error: unknown pattern." << endl;
}

// =============================================================================
// =============================================================================
void square( int       rows,
             int       cols,
             ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = x;
         py = y;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=0; y<rows-1; y++ )
   {
      for( int x=0; x<cols-1; x++ )
      {
         out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                     << ((x+1)+(y+0)*cols)+1 << " "
                     << ((x+1)+(y+1)*cols)+1 << " "
                     << ((x+0)+(y+1)*cols)+1 << endl;
      }
   }
}

// =============================================================================
// =============================================================================
void triangle( int       rows,
               int       cols,
               ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = x + 0.5f*y;
         py = y * sqrtf(3.0f)/2.0f;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=0; y<rows-1; y++ )
   {
      for( int x=0; x<cols-1; x++ )
      {
         out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                     << ((x+1)+(y+0)*cols)+1 << " "
                     << ((x+0)+(y+1)*cols)+1 << endl;

         out << "f " << ((x+1)+(y+0)*cols)+1 << " "
                     << ((x+1)+(y+1)*cols)+1 << " "
                     << ((x+0)+(y+1)*cols)+1 << endl;
      }
   }
}

// =============================================================================
// =============================================================================
void hexagon( int       rows,
              int       cols,
              ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf((x+(y%2))/2.0f)*3.0f + ((x+y)%2) - (y%2)*1.5f;
         py = y * sqrtf(3.0f)/2.0f;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=0; y<rows-2; y++ )
   {
      for( int x=0; x<cols-1; x++ )
      {
         if(( y%2 == 0 && x%2 == 0 ) ||
            ( y%2 == 1 && x%2 == 1 ))
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+1)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi1( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = x + 0.5f*y;
         py = y * sqrtf(3.0f)/2.0f;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=1; y<rows-1; y++ )
   {
      for( int x=1; x<cols-1; x++ )
      {
         int i = (x+3*y)%7;

         if( i == 0 ||
             i == 2 ||
             i >= 5 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( i == 2 ||
             i >= 4 )
         {
            out << "f " << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( i == 4 )
         {
            out << "f " << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y-1)*cols)+1 << " "
                        << ((x+1)+(y-1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi2( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf(x/2.0f)*(2.0f+sqrtf(2.0f)) + (x%2) +
              floorf(y/2.0f)*(1.0f+sqrtf(2.0f)/2.0f);
         py = floorf(y/2.0f)*(1.0f+sqrtf(2.0f)/2.0f) + (y%2);

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=1; y<rows-2; y++ )
   {
      for( int x=1; x<cols-2; x++ )
      {
         if( x%2 == 1 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y-1)*cols)+1 << " "
                        << ((x+2)+(y-1)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x-1)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
   
   for( int y=0; y<rows-1; y++ )
   {
      for( int x=0; x<cols-1; x++ )
      {
         if( x%2 == 0 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi3( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = x + floorf(y/2.0f)*0.5f;
         py = floorf(y/2.0f)*(1.0f+sqrtf(3.0f)/2.0f) + (y%2);

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=0; y<rows-1; y++ )
   {
      for( int x=0; x<cols-1; x++ )
      {
         if( y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
         else
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
            out << "f " << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi4( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = x+0.5f*y;
         py = y*sqrtf(3.0f)/2.0f;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }


   // write faces ----------------------------------------------------
   for( int y=0; y<rows-2; y++ )
   {
      for( int x=1; x<cols-1; x++ )
      {
         if( x%2 == 0 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 0 && y%2 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 1 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x-1)+(y+2)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi5( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf(x/2.0f)*(1.0f+sqrtf(3.0f)/2.0f) + (x%2) -
              floorf(y/2.0f)*0.5f;
         py = floorf(y/2.0f)*(1.0f+sqrtf(3.0f)/2.0f) + (y%2) +
              floorf(x/2.0f)*0.5f;

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=0; y<rows-1; y++ )
   {
      for( int x=1; x<cols-1; x++ )
      {
         if( x%2 == 0 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 1 && y%2 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 0 && y%2 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << endl;

            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 1 && y%2 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi6( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf(x/2.0f)*(2.0f+sqrtf(3.0f)) + (x%2) +
              floorf(y/4.0f)*(1.0f+sqrtf(3.0f)/2.0f);
         py = floorf(y/4.0f)*(1.5f+sqrtf(3.0f));

         switch( y%4 )
         {
            case 0:
               px += 0.0f;
               py += 0.0f;
               break;
            case 1:
               px += 0.5f;
               py += sqrtf(3.0f)/2.0f;
               break;
            case 2:
               px += 0.5f;
               py += 1.0f + sqrtf(3.0f)/2.0f;
               break;
            case 3:
               px += 0.0f;
               py += 1.0f + sqrtf(3.0f);
               break;
            default:
               break;
         }

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=1; y<rows-4; y++ )
   {
      for( int x=0; x<cols-3; x++ )
      {
         if( x%2 == 0 && y%4 == 0 )
         {
            out << "f " << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+2)+(y-1)*cols)+1 << " "
                        << ((x+3)+(y-1)*cols)+1 << " "
                        << ((x+2)+(y+0)*cols)+1 << " "
                        << ((x+2)+(y+1)*cols)+1 << " "
                        << ((x+2)+(y+2)*cols)+1 << " "
                        << ((x+2)+(y+3)*cols)+1 << " "
                        << ((x+1)+(y+4)*cols)+1 << " "
                        << ((x+0)+(y+4)*cols)+1 << " "
                        << ((x+1)+(y+3)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

         }

         if( x%2 == 0 && y%4 == 2 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi7( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf(x/2.0f)*(1.0f+sqrtf(3.0f)) + (x%2)*sqrtf(3.0f) +
              floorf(y/4.0f)*(0.5f+sqrtf(3.0f)/2.0f);
         py = floorf(y/4.0f)*(1.5f+sqrtf(3.0f)/2.0f);

         switch( y%4 )
         {
            case 0:
               px += sqrtf(3.0f)/2.0f;
               py += -0.5f;
               break;
            case 1:
               px += 0.0f;
               py += 0.0f;
               break;
            case 2:
               px += 0.0f;
               py += 1.0f;
               break;
            case 3:
               px += sqrtf(3.0f)/2.0f;
               py += 1.5f;
               break;
            default:
               break;
         }

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=2; y<rows-3; y++ )
   {
      for( int x=2; x<cols-2; x++ )
      {
         if( x%2 == 0 && y%4 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+1)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+3)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+2)+(y-2)*cols)+1 << " "
                        << ((x+2)+(y-1)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << endl;

            out << "f " << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+2)+(y-1)*cols)+1 << " "
                        << ((x+2)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 1 && y%4 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;

         }
         
         if( x%2 == 1 && y%4 == 2 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x-1)+(y+2)*cols)+1 << " "
                        << ((x-1)+(y+3)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << endl;
         }

         if( x%2 == 0 && y%4 == 2 )
         {
            out << "f " << ((x-1)+(y+0)*cols)+1 << " "
                        << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x-2)+(y+2)*cols)+1 << endl;

         }
      }
   }
}

// =============================================================================
// =============================================================================
void semi8( int       rows,
            int       cols,
            ofstream& out )
{
   // write vertices -------------------------------------------------
   float px, py;

   for( int y=0; y<rows; y++ )
   {
      for( int x=0; x<cols; x++ )
      {
         px = floorf(x/4.0f)*(3.0f+3.0f*sqrtf(3.0f)) +
              floorf(y/4.0f)*(1.5f+1.5f*sqrtf(3.0f));
         py = floorf(y/4.0f)*(1.5f+sqrtf(3.0f)/2.0f);

         switch( y%4 )
         {
            case 0:
               px += sqrtf(3.0f)/2.0f;
               py += -0.5f;
               break;
            case 1:
               px += 0.0f ;
               py += 0.0f ;
               break;
            case 2:
               px += 0.0f ;
               py += 1.0f;
               break;
            case 3:
               px += sqrtf(3.0f)/2.0f;
               py += 1.5f;
               break;
            default:
               break;
         }

         switch( x%4 )
         {
            case 0:
               px += 0.0f;
               break;
            case 1:
               px += sqrtf(3.0f);
               break;
            case 2:
               px += 1.0f + sqrtf(3.0f);
               break;
            case 3:
               px += 1.0f + 2.0f*sqrtf(3.0f);
               break;
         }

         out << "v " << px << " " << py << " 0.0" << endl;
      }
   }

   // write faces ----------------------------------------------------
   for( int y=3; y<rows-4; y++ )
   {
      for( int x=3; x<cols-3; x++ )
      {
         if( x%2 == 0 && y%4 == 0 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+1)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+3)*cols)+1 << " "
                        << ((x+0)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( x%4 == 1 && y%4 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }

         if( x%4 == 3 && y%4 == 2 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x-3)+(y+2)*cols)+1 << " "
                        << ((x-3)+(y+3)*cols)+1 << " "
                        << ((x-1)+(y+1)*cols)+1 << endl;
         }

         if( x%4 == 0 && y%4 == 2 )
         {
            out << "f " << ((x+0)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+3)*cols)+1 << " "
                        << ((x-2)+(y+2)*cols)+1 << " "
                        << ((x+0)+(y+0)*cols)+1 << endl;
         }

         if( x%4 == 3 && y%4 == 1 )
         {
            out << "f " << ((x+0)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y-2)*cols)+1 << " "
                        << ((x+2)+(y-3)*cols)+1 << " "
                        << ((x+3)+(y-3)*cols)+1 << " "
                        << ((x+3)+(y-2)*cols)+1 << " "
                        << ((x+1)+(y+0)*cols)+1 << " "
                        << ((x+1)+(y+1)*cols)+1 << " "
                        << ((x-1)+(y+3)*cols)+1 << " "
                        << ((x-1)+(y+4)*cols)+1 << " "
                        << ((x-2)+(y+4)*cols)+1 << " "
                        << ((x-3)+(y+3)*cols)+1 << " "
                        << ((x+0)+(y+1)*cols)+1 << endl;
         }
      }
   }
}

