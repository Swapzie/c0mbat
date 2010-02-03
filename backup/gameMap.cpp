#include "gameMap.h"

using namespace std;

GameMap::GameMap(string level, SDL_Surface *map_sprites,
                 SDL_Surface *map_border_sprites, int tileSize = 32)
{
    
    m_tileSize = tileSize;
    m_sprites = map_sprites;
    m_border_sprites = map_border_sprites;

    read_from_file(level);
    parse_borders();
}


GameMap::~GameMap()
{
    for (int i=0; i< m_width; i++)
        delete[] m_map_matrix[i];
    delete[] m_map_matrix;
}

void GameMap::read_from_file(string file)
{
    file = "./Maps/" + file + ".txt";
    //file += ".txt";
    char fileName[64]; //with appended .txt
    fstream myFile;

    for(unsigned int i=0; i <= file.length(); i++)
        fileName[i] = file[i];   

    myFile.open(fileName, ios::in);
    if(myFile.is_open())
    {

        m_width = 9;//TODO: parse this from file header!
        m_height = 6;//TODO: parse this from file header!

        string parameters;
        getline(myFile, parameters);
        
        stringstream sin(stringstream::in);


        istringstream(parameters) >> m_width >> m_height;


        
        m_map_matrix = new char*[m_width];

        for(int i=0; i<m_width; i++)
            m_map_matrix[i] = new char[m_height];

        string line;
        char temp;

        int linesRead = 0;
        while(linesRead < m_height && myFile.peek() != EOF){
            getline(myFile, line);
            
            for(int i=0; i<m_width; i++){
                temp = line[i];
    
                if(temp >= '0' && temp <= '9')
                    m_map_matrix[i][linesRead] = temp - '0'; 

                else if(temp >= 'A' && temp <= 'Z')
                    m_map_matrix[i][linesRead] = temp - 'A' +10;

                else if(temp >= 'a' && temp <= 'z')
                    m_map_matrix[i][linesRead] = temp - 'a' + 36;
                
                else if(temp == ' ')
                    m_map_matrix[i][linesRead] = 0;

                else
                    m_map_matrix[i][linesRead] = '~'; 

            }

            ++linesRead;
        }
    }
    else
        cerr << file << " could not be opened." << endl;
}

void GameMap::parse_borders()
{
    
    m_map_borders = new char*[m_width*2];

    for(int i=0; i<m_width*2; i++)
        m_map_borders[i] = new char[m_height*2];

    
    for(int x=0; x<m_width*2; x++)
        for(int y=0; y<m_height*2; y++)
            m_map_borders[x][y] = 0;


    for(int x=0; x<m_width*2; x++)
        for(int y=0; y<m_height*2; y++)
            m_map_borders[x][y] = find_tile(x,y);
}

int GameMap::find_tile(int testX, int testY)
{ // Here be dragons... and black magic..
    int corner_tile = 18; //if you F this up, you'll notice

    int mapX = testX/2;
    int mapY = testY/2;

    //bool flags for signaling if key squares are filled
    bool vertical = true, horizontal = true, diagonal = true; 
    
    
    if(m_map_matrix[mapX][mapY] == 1){
        if(testX%2 == 0){ 
            if(testY%2 == 0) { //Top-left tile
                corner_tile = 0;
            }
            else                //Bottom left
                corner_tile = 13;
        }
        else{                   //Top Right
            if (testY%2 == 0)
                corner_tile = 13;
            else                //Bottom Left
                corner_tile = 9;
        }
    }

    else if(m_map_matrix[mapX][mapY] == 2){
        if(testX%2 == 0){ 
            if(testY%2 == 0) { //Top-left tile
                corner_tile = 14;
            }
            else                //Bottom left
                corner_tile = 10;
        }
        else{                   //Top Right
            if (testY%2 == 0)
                corner_tile = 0;
            else                //Bottom Left
                corner_tile = 14;
        }
    }


    else if(m_map_matrix[mapX][mapY] == 3){
        if(testX%2 == 0){ 
            if(testY%2 == 0) {  
                corner_tile = 15;
            }
            else                
                corner_tile = 0;
        }
        else{                   
            if (testY%2 == 0)
                corner_tile = 11;
            else                
                corner_tile = 15;
        }
    }


    else if(m_map_matrix[mapX][mapY] == 4){
        if(testX%2 == 0){
            if(testY%2 == 0) { 
                corner_tile = 12;
            }
            else
                corner_tile = 16;
        }
        else{
            if (testY%2 == 0)
                corner_tile = 16;
            else
                corner_tile = 0;
        }
    }
    else if(m_map_matrix[mapX][mapY] == 5){
        if(testX%2 == 0){
            if(testY%2 == 0) { //Top-left tile

                if(mapX > 0 && mapY < m_height)
                    if(m_map_matrix[mapX-1][mapY] == 0)
                        horizontal = false;

                if(mapX < m_width && mapY > 0)
                    if(m_map_matrix[mapX][mapY-1] == 0)
                        vertical = false;

                if(mapX > 0 && mapY > 0)
                    if(m_map_matrix[mapX-1][mapY-1] == 0)
                        diagonal = false;


                if(horizontal)
                    if(vertical)
                        if(diagonal)
                            corner_tile = 17;
                        
                        else
                            corner_tile = 9;
                    else
                        corner_tile = 1;
                
                else if(vertical)
                    corner_tile = 3;
                else
                    corner_tile = 5;
            }
        // 0x  0x  5x  5x  50  
        // 05   0  00  05  55  
            else{ //Bottom-left tile
                if(mapX > 0 && mapY < m_height)
                    if(m_map_matrix[mapX-1][mapY] == 0)
                        horizontal = false;

                if(mapX < m_width && mapY < m_height-1)
                    if(m_map_matrix[mapX][mapY+1] == 0)
                        vertical = false;

                if(mapX > 0 && mapY < m_height-1)
                    if(m_map_matrix[mapX-1][mapY+1] == 0)
                        diagonal = false;


                if(horizontal)
                    if(vertical)
                        if(diagonal)
                            corner_tile = 17;
                        
                        else
                            corner_tile = 11;
                    else
                        corner_tile = 4;
                
                else if(vertical)
                    corner_tile = 3;
                else
                    corner_tile = 7;
            }
        }
        // 00  0   50  50  55  
        // x5  x0  x0  x5  05  
        else if(testY%2 == 0){ //Top-right tile

            if(mapX < m_width-1 && mapY < m_height)
                if(m_map_matrix[mapX+1][mapY] == 0)
                    horizontal = false;

            if(mapX < m_width && mapY > 0)
                if(m_map_matrix[mapX][mapY-1] == 0)
                    vertical = false;

            if(mapX < m_width-1 && mapY > 0)
                if(m_map_matrix[mapX+1][mapY-1] == 0)
                    diagonal = false;


            if(horizontal)
                if(vertical)
                    if(diagonal)
                        corner_tile = 17;
                    
                    else
                        corner_tile = 10;
                else
                    corner_tile = 1;
            
            else if(vertical)
                corner_tile = 2;
            else
                corner_tile = 6;
        }
        // x5  x0  x0  x5  05
        // 00  0   50  50  55
        else{ // Bottom-right tile


                if(mapX < m_width-1 && mapY < m_height)
                    if(m_map_matrix[mapX+1][mapY] == 0)
                        horizontal = false;

                if(mapX < m_width && mapY < m_height-1)
                    if(m_map_matrix[mapX][mapY+1] == 0)
                        vertical = false;

                if(mapX < m_width-1 && mapY < m_height-1)
                    if(m_map_matrix[mapX+1][mapY+1] == 0)
                        diagonal = false;


                if(horizontal)
                    if(vertical)
                        if(diagonal)
                            corner_tile = 17;
                        
                        else
                            corner_tile = 12;
                    else
                        corner_tile = 4;
                
                else if(vertical)
                    corner_tile = 2;
                else
                    corner_tile = 8;
        }
    }
    else
        corner_tile = 0;

    return corner_tile;
}

void GameMap::draw(SDL_Surface *screen)
{
    SDL_Rect *targetRect = new SDL_Rect;
    targetRect->h = m_tileSize;
    targetRect->w = m_tileSize; 
    
    SDL_Rect *sourceRect = new SDL_Rect;
    sourceRect -> h = m_tileSize;
    sourceRect -> w = m_tileSize;
    sourceRect -> x = 5 * m_tileSize;
    sourceRect -> y = 0;

/*
    for(int y=0; y<11; y++){
        for(int x=0; x < m_width; x++){
            if(m_map_matrix[x][y] > 0 && 
               m_map_matrix[x][y] < 36)
            {
                sourceRect -> x = m_tileSize * m_map_matrix[x][y];

                targetRect->x = x * m_tileSize;
                targetRect->y = y * m_tileSize;
                
                SDL_BlitSurface(m_sprites, sourceRect, screen, targetRect);
            }
        }
    }
    */
    SDL_Rect *bordersSource = new SDL_Rect;
    bordersSource -> h = m_tileSize/2;
    bordersSource -> w = m_tileSize/2;
    bordersSource -> x = 1 * m_tileSize/2;
    bordersSource -> y = 0;
    
    SDL_Rect *bordersTarget = new SDL_Rect;
    bordersTarget -> h = m_tileSize/2;
    bordersTarget -> w = m_tileSize/2;
    bordersTarget -> x = 5 * m_tileSize/2;
    bordersTarget -> y = 6 * m_tileSize/2;

    for(int y=0; y<22; y++){
        for(int x=0; x < m_width*2; x++){
            if(m_map_borders[x][y] > 0)
            {

                bordersSource -> x = m_map_borders[x][y] * m_tileSize/2;

                bordersTarget -> x = x * m_tileSize/2;
                bordersTarget -> y = y * m_tileSize/2;

                SDL_BlitSurface(m_border_sprites, bordersSource, 
                                screen, bordersTarget);
            }
            
        }
    }
}

char GameMap::tile_at(int x, int y)
{
    return m_map_matrix[x][y]; 
}

void GameMap::print(ostream &out)
{ //prints the map to out, values 10-35 is A-Z, values 35-61 is a-z
    char tempchar;

    out << "Map size is x: " << m_width << " y: " << m_height << endl;
    out << "Map texture is: " << "[not implemented yet]\n";


    for(int y=0; y < m_height; y++){
        for(int x=0; x < m_width; x++)
        {
            if(m_map_matrix[x][y] == 0)
                out << "  ";
            else if(m_map_matrix[x][y] < 10)
                out << (int) m_map_matrix[x][y] << " ";
            else if(m_map_matrix[x][y] <= 35){
                tempchar = m_map_matrix[x][y] + 'A' - 10;
                out << tempchar << " ";
                
            }
            else{
                tempchar = m_map_matrix[x][y] + 'a' - 36;
                out << tempchar << " ";
            }
        }
        out << endl;
    }
}

void GameMap::print_int(ostream &out)
{
    out << "Printing map values, cast to integers: \n\n";

    for(int y=0; y < m_height; y++){
        for(int x=0; x < m_width; x++)
        {
            if(m_map_matrix[x][y] == '0')
                out << "  ";
            else 
                out << (int) m_map_matrix[x][y] << " ";
        }
        out << endl;
    }
}

