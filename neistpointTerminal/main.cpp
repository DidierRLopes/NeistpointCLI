//
//Users/DidierRodriguesLopes/Documents/git/neistpointTerminal/  main.cpp
//  neistpointTerminal
//
//  Created by Didier Rodrigues Lopes on 05/07/2019.
//  Copyright © 2019 Didier Lopes. All rights reserved.
//

/*
#include <iostream>
#include <fstream>
#include <sstream>
#include "database.hpp"

#define NUM_SIZES      6
#define NUM_MATERIALS  8
#define NUM_PRODUCTS   12

int materialToRequest[NUM_MATERIALS][NUM_SIZES];
int materialShipping[NUM_MATERIALS][NUM_SIZES];
int materialInStock[NUM_MATERIALS][NUM_SIZES];

int productToCreate[NUM_PRODUCTS][NUM_SIZES];
int productCreating[NUM_PRODUCTS][NUM_SIZES];
int productInStock[NUM_PRODUCTS][NUM_SIZES];
int productSent[NUM_PRODUCTS][NUM_SIZES];


std::string sizes[NUM_SIZES] = {"XS", "S", "M", "L", "XL", "XXL"};

std::string materials[NUM_MATERIALS] =
                        {
                            "White Shirt",
                            "Grey Shirt",
                            "Navy Shirt",
                            "Black Shirt",
                            "Yellow Sweater",
                            "Grey Sweater",
                            "Navy Sweater",
                            "Black Sweater"
                        };

std::string products[NUM_PRODUCTS] =
                        {
                            "The Vintage White (Black) Shirt",
                            "The Vintage White (Red-black) Shirt",
                            "The Plain White (Black) Shirt",
                            "The Classic Grey (Black) Shirt",
                            "The Original Navy (Yellow) Shirt",
                            "The Vintage Navy (White-yellow) Shirt",
                            "The Vintage Black (White) Shirt",
                            "The Original Yellow (Black-White) Sweater",
                            "The Original Grey (Black) Sweater",
                            "The Vintage Grey (Black) Sweater",
                            "The Original B. Navy (White) Sweater",
                            "The Vintage B. Black (White-pink) Sweater"
                        };

void load_database()
{
    std::ifstream file("db17.csv");
    std::string line;
    
    for (int material = 0; material <= NUM_MATERIALS; material++)
    {
        // This was a pain in the ass because file was saved as CRLF instead of LF
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (material == 0 || size == 0)
            {
                // Jump material name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> materialToRequest[material-1][size-1];
        }

        if (material == NUM_MATERIALS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    for (int material = 0; material <= NUM_MATERIALS; material++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (material == 0 || size == 0)
            {
                // Jump material name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> materialShipping[material-1][size-1];
        }

        if ( material == NUM_MATERIALS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    for (int material = 0; material <= NUM_MATERIALS; material++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (material == 0 || size == 0)
            {
                // Jump material name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> materialInStock[material-1][size-1];
        }

        if ( material == NUM_MATERIALS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    for (int product = 0; product <= NUM_PRODUCTS; product++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (product == 0 || size == 0)
            {
                // Jump product name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> productToCreate[product-1][size-1];
        }

        if (product == NUM_PRODUCTS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    
    for (int product = 0; product <= NUM_PRODUCTS; product++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (product == 0 || size == 0)
            {
                // Jump product name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> productCreating[product-1][size-1];
        }

        if ( product == NUM_PRODUCTS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    for (int product = 0; product <= NUM_PRODUCTS; product++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (product == 0 || size == 0)
            {
                // Jump product name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> productInStock[product-1][size-1];
        }
        
        if (product == NUM_PRODUCTS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
    
    for (int product = 0; product <= NUM_PRODUCTS; product++)
    {
        std::getline(file, line, '\n');
        std::istringstream buffer(line);
        
        for (int size = 0; size <= NUM_SIZES; size++)
        {
            std::string val;
            std::getline(buffer, val, ';');
            
            if (product == 0 || size == 0)
            {
                // Jump product name and size
                continue;
            }
            
            std::stringstream field(val);
            field >> productSent[product-1][size-1];
        }

        if ( product == NUM_PRODUCTS)
        {
            // burn line
            std::getline(file, line, '\n');
        }
    }
}

void save_database()
{
    std::ofstream file("db17.csv");
    
    if (!file.is_open())
    {
        std::cout << "Unable to open file";
        return;
    }
    
    file << "MATERIAL TO REQUEST;XS;S;M;L;XL;XXL;\n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        file << materials[material] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << materialToRequest[material][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "MATERIAL SHIPPING;XS;S;M;L;XL;XXL;\n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        file << materials[material] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << materialShipping[material][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "MATERIAL IN STOCK;XS;S;M;L;XL;XXL;\n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        file << materials[material] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << materialInStock[material][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "PRODUCT TO CREATE;XS;S;M;L;XL;XXL;\n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        file << products[product] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << productToCreate[product][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "PRODUCT CREATING;XS;S;M;L;XL;XXL;\n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        file << products[product] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << productCreating[product][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "PRODUCT IN STOCK;XS;S;M;L;XL;XXL;\n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        file << products[product] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << productInStock[product][size] << ";";
        }
        file << "\n";
    }
    file << "\n";
    
    file << "PRODUCT SENT;XS;S;M;L;XL;XXL;\n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        file << products[product] << ";";
        for (int size = 0; size < NUM_SIZES; size++)
        {
            file << productSent[product][size] << ";";
        }
        file << "\n";
    }
    
    file.close();
}

void show_material2request()
{
    std::cout << "MATERIAL TO REQUEST  |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        std::cout << "---------------------------------------------------------\n";
        
        std::cout << materials[material];
        for (int i = (int) materials[material].length(); i<=20 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (materialToRequest[material][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (materialToRequest[material][size] < 9)
            {
                std::cout << "|  " << materialToRequest[material][size] << "  ";
            }
            else if (materialToRequest[material][size] < 99)
            {
                std::cout << "|  " << materialToRequest[material][size] << " ";
            }
            else
            {
                std::cout << "| " << materialToRequest[material][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void show_materialShipping()
{
    std::cout << "MATERIAL SHIPPING    |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        std::cout << "---------------------------------------------------------\n";
        
        std::cout << materials[material];
        for (int i = (int) materials[material].length(); i<=20 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (materialShipping[material][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (materialShipping[material][size] < 10)
            {
                std::cout << "|  " << materialShipping[material][size] << "  ";
            }
            else if (materialShipping[material][size] < 100)
            {
                std::cout << "|  " << materialShipping[material][size] << " ";
            }
            else
            {
                std::cout << "| " << materialShipping[material][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void show_materialStock()
{
    std::cout << "MATERIAL IN STOCK    |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int material = 0; material < NUM_MATERIALS; material++)
    {
        std::cout << "---------------------------------------------------------\n";
        
        std::cout << materials[material];
        for (int i = (int) materials[material].length(); i<=20 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (materialInStock[material][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (materialInStock[material][size] < 9)
            {
                std::cout << "|  " << materialInStock[material][size] << "  ";
            }
            else if (materialInStock[material][size] < 99)
            {
                std::cout << "|  " << materialInStock[material][size] << " ";
            }
            else
            {
                std::cout << "| " << materialInStock[material][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void show_product2create()
{
    std::cout << "PRODUCT TO CREATE                         |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        std::cout << "------------------------------------------------------------------------------\n";
        
        std::cout << products[product];
        for (int i = (int) products[product].length(); i<=41 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (productToCreate[product][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (productToCreate[product][size] < 9)
            {
                std::cout << "|  " << productToCreate[product][size] << "  ";
            }
            else if (productToCreate[product][size] < 99)
            {
                std::cout << "|  " << productToCreate[product][size] << " ";
            }
            else
            {
                std::cout << "| " << productToCreate[product][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void show_productCreating()
{
    std::cout << "PRODUCT IN CREATION                       |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        std::cout << "------------------------------------------------------------------------------\n";
        
        std::cout << products[product];
        for (int i = (int) products[product].length(); i<=41 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (productCreating[product][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (productCreating[product][size] < 9)
            {
                std::cout << "|  " << productCreating[product][size] << "  ";
            }
            else if (productCreating[product][size] < 99)
            {
                std::cout << "|  " << productCreating[product][size] << " ";
            }
            else
            {
                std::cout << "| " << productCreating[product][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void show_productStock()
{
    std::cout << "PRODUCT IN STOCK                          |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        std::cout << "------------------------------------------------------------------------------\n";
        
        std::cout << products[product];
        for (int i = (int) products[product].length(); i<=41 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (productInStock[product][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (productInStock[product][size] < 9)
            {
                std::cout << "|  " << productInStock[product][size] << "  ";
            }
            else if (productInStock[product][size] < 99)
            {
                std::cout << "|  " << productInStock[product][size] << " ";
            }
            else
            {
                std::cout << "| " << productInStock[product][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void show_productSent()
{
    std::cout << "PRODUCT SOLD                              |  XS |  S  |  M  |  L  |  XL | XXL \n";
    for (int product = 0; product < NUM_PRODUCTS; product++)
    {
        std::cout << "------------------------------------------------------------------------------\n";
        
        std::cout << products[product];
        for (int i = (int) products[product].length(); i<=41 ; i++)
        {
            std::cout << " ";
        }
        for (int size = 0; size < NUM_SIZES; size++)
        {
            if (productSent[product][size] == 0)
            {
                std::cout << "|     ";
            }
            else if (productSent[product][size] < 9)
            {
                std::cout << "|  " << productSent[product][size] << "  ";
            }
            else if (productSent[product][size] < 99)
            {
                std::cout << "|  " << productSent[product][size] << " ";
            }
            else
            {
                std::cout << "| " << productSent[product][size] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void order_material()
{
    std::cout << "What material was ordered from Stanley?\n";
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    bool toChoose = true;
    int matChosen;
    int sizeChosen;
    int quantChosen;
    
    while (toChoose)
    {
        for (int material = 0; material < NUM_MATERIALS; material++)
        {
            std::cout << material+1 << " - " << materials[material] << "\n";
        }
        std::cout << "MATERIAL: ";
        std::cin >> matChosen;
        matChosen--;
        
        if (matChosen == -1)
        {
            return;
        }
        if (matChosen < 0 || matChosen > NUM_MATERIALS-1)
        {
            std::cout << "ERROR - SELECT A VALID MATERIAL\n\n";
            continue;
        }
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            std::cout << size+1 << " - " << sizes[size] << "\n";
        }
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (matChosen == -1)
        {
            return;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << "ERROR - SELECT A VALID ID\n\n";
            continue;
        }
        
        std::cout << "QUANTITY: ";
        std::cin >> quantChosen;
        
        toChoose = false;
        
        materialToRequest[matChosen][sizeChosen]-=quantChosen;
        // This is allowed because we can order things that were not required by costumers
        if (materialToRequest[matChosen][sizeChosen]<0)
        {
            materialToRequest[matChosen][sizeChosen]=0;
        }
        materialShipping[matChosen][sizeChosen]+=quantChosen;
        
        std::cout << quantChosen << " " << sizes[sizeChosen] << " " << materials[matChosen] << " were ordered!\n\n";
    }
}

bool material_arrived()
{
    int c;
    
    do
    {
        std::cout << "What material has arrived?\n";
        std::cout << "(Option '0' will take you back to the menu)\n\n";
        std::cout << "1 - All requested material\n";
        std::cout << "2 - Only some material\n";
        
        std::cin >> c;
        
        if (c == 0)
        {
            return false;
        }
        
        if (c == 1)
        {
            std::cout << "The following material will be added to the Material stock\n";
            show_materialShipping();
            
            char r;
            do
            {
                std::cout << "Do you confirm? (y-yes, n-no)\n";
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int material = 0; material < NUM_MATERIALS; material++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            materialInStock[material][size] +=  materialShipping[material][size];
                            materialShipping[material][size]=0;
                        }
                    }
                    return true;
                }
                
                if (r == 'n')
                {
                    return false;
                }
                    
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            int matChosen;
            int sizeChosen;
            int quantChosen;
            
            while (1)
            {
                for (int material = 0; material < NUM_MATERIALS; material++)
                {
                    std::cout << material+1 << " - " << materials[material] << "\n";
                }
                std::cout << "MATERIAL: ";
                std::cin >> matChosen;
                matChosen--;
                
                if (matChosen == -1)
                {
                    return false;
                }
                if (matChosen < 0 || matChosen > NUM_MATERIALS-1)
                {
                    std::cout << "ERROR - SELECT A VALID MATERIAL\n\n";
                    continue;
                }
                
                for (int size = 0; size < NUM_SIZES; size++)
                {
                    std::cout << size+1 << " - " << sizes[size] << "\n";
                }
                std::cout << "SIZE: ";
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (matChosen == -1)
                {
                    return false;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << "ERROR - SELECT A VALID ID\n\n";
                    continue;
                }
                
                std::cout << "QUANTITY: ";
                std::cin >> quantChosen;
                
                if (quantChosen > materialShipping[matChosen][sizeChosen])
                {
                    std::cout << "It is not possible that more material than expected has arrived!\n\n";
                    return false;
                }
                
                materialShipping[matChosen][sizeChosen]-=quantChosen;
                materialInStock[matChosen][sizeChosen]+=quantChosen;
                std::cout << quantChosen << " " << sizes[sizeChosen] << " " << materials[matChosen] << " has arrived!\n\n";
                
                return true;
            }
        }
    } while (c < 0 || c > 2);
    
    return false;
}

bool order_product()
{
    std::cout << "What product will Sr. Luis produce?\n";
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int proChosen;
    int sizeChosen;
    int quantChosen;
    
    while (1)
    {
        for (int product = 0; product < NUM_PRODUCTS; product++)
        {
            std::cout << product+1 << " - " << products[product] << "\n";
        }
        std::cout << "PRODUCT: ";
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << "ERROR - SELECT A VALID MATERIAL\n\n";
            continue;
        }
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            std::cout << size+1 << " - " << sizes[size] << "\n";
        }
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << "ERROR - SELECT A VALID ID\n\n";
            continue;
        }
        
        std::cout << "QUANTITY: ";
        std::cin >> quantChosen;
        
        switch(proChosen)
        {
            case 0:
            case 1:
            case 2:
                if (quantChosen > materialInStock[0][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[0][sizeChosen]-=quantChosen;
                break;
            case 3:
                if (quantChosen > materialInStock[1][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[1][sizeChosen]-=quantChosen;
                break;
            case 4:
            case 5:
                if (quantChosen > materialInStock[2][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[2][sizeChosen]-=quantChosen;
                break;
            case 6:
                if (quantChosen > materialInStock[3][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[3][sizeChosen]-=quantChosen;
                break;
            case 7:
                if (quantChosen > materialInStock[4][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[4][sizeChosen]-=quantChosen;
                break;
            case 8:
            case 9:
                if (quantChosen > materialInStock[5][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[5][sizeChosen]-=quantChosen;
                break;
            case 10:
                if (quantChosen > materialInStock[6][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[6][sizeChosen]-=quantChosen;
                break;
            case 11:
                if (quantChosen > materialInStock[7][sizeChosen])
                {
                    std::cout << "You do not have material in stock to produce that product!\n";
                    return false;
                }
                materialInStock[7][sizeChosen]-=quantChosen;
                break;
        }
        productToCreate[proChosen][sizeChosen]+=quantChosen;
        std::cout << quantChosen << " " << sizes[sizeChosen] << " " << products[proChosen] << " needs to be created at Sr. Luis!\n\n";
        
        return true;
    }
    
    return true;
}

bool product_arrived()
{
    int c;
    
    do
    {
        std::cout << "What product will Sr. Luis produce?\n";
        std::cout << "(Option '0' will take you back to the menu)\n";
        std::cout << "1 - All requested products\n";
        std::cout << "2 - Only some material\n";
        
        std::cin >> c;
        
        if (c == 0)
        {
            return false;
        }
        
        if (c == 1)
        {
            std::cout << "The following products will be added to the Product stock\n";
            show_product2create();
            
            char r;
            do
            {
                std::cout << "Do you confirm? (y-yes, n-no)\n";
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int product = 0; product < NUM_PRODUCTS; product++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            productInStock[product][size] +=  productToCreate[product][size];
                            productToCreate[product][size]=0;
                        }
                    }
                    return true;
                }
                
                if (r == 'n')
                {
                    return false;
                }
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            int proChosen;
            int sizeChosen;
            int quantChosen;
            
            while (1)
            {
                for (int product = 0; product < NUM_PRODUCTS; product++)
                {
                    std::cout << product+1 << " - " << products[product] << "\n";
                }
                std::cout << "PRODUCT: ";
                std::cin >> proChosen;
                proChosen--;
                
                if (proChosen == -1)
                {
                    return false;
                }
                if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
                {
                    std::cout << "ERROR - SELECT A VALID MATERIAL\n\n";
                    continue;
                }
                
                for (int size = 0; size < NUM_SIZES; size++)
                {
                    std::cout << size+1 << " - " << sizes[size] << "\n";
                }
                std::cout << "SIZE: ";
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (proChosen == -1)
                {
                    return false;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << "ERROR - SELECT A VALID ID\n\n";
                    continue;
                }
                
                std::cout << "QUANTITY: ";
                std::cin >> quantChosen;
                
                if (quantChosen > productToCreate[proChosen][sizeChosen])
                {
                    std::cout << "It is not possible to have arrived more products than the ones in production!\n";
                }
                productToCreate[proChosen][sizeChosen]-=quantChosen;
                productInStock[proChosen][sizeChosen]+=quantChosen;
                std::cout << quantChosen << " " << sizes[sizeChosen] << " " << products[proChosen] << " arrived from Sr. Luis!\n\n";
                
                return true;
            }
        }
    } while (c < 0 || c > 2);
    
    return false;
}

bool product_dispatched()
{
    std::cout << "What product was dispatched?\n";
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int proChosen;
    int sizeChosen;
    int quantChosen;
    
    while (1)
    {
        for (int product = 0; product < NUM_PRODUCTS; product++)
        {
            std::cout << product+1 << " - " << products[product] << "\n";
        }
        std::cout << "PRODUCT: ";
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << "ERROR - SELECT A VALID MATERIAL\n\n";
            continue;
        }
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            std::cout << size+1 << " - " << sizes[size] << "\n";
        }
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << "ERROR - SELECT A VALID ID\n\n";
            continue;
        }
        
        std::cout << "QUANTITY: ";
        std::cin >> quantChosen;
        
        if (quantChosen > productInStock[proChosen][sizeChosen])
        {
            std::cout << "It is not possible to have sold more products than the ones in stock\n";
            return false;
        }
    
        productInStock[proChosen][sizeChosen]-=quantChosen;
        productSent[proChosen][sizeChosen]+=quantChosen;
        
        std::cout << quantChosen << " " << sizes[sizeChosen] << " " << products[proChosen] << " sent!\n\n";
        return true;
    }
    
    return true;
}

bool new_product()
{
    std::cout << "What product does the costumer wants?\n";
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int proChosen;
    int sizeChosen;
    
    while (1)
    {
        for (int product = 0; product < NUM_PRODUCTS; product++)
        {
            std::cout << product+1 << " - " << products[product] << "\n";
        }
        std::cout << "PRODUCT: ";
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << "ERROR - SELECT A VALID PRODUCT\n\n";
            continue;
        }
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            std::cout << size+1 << " - " << sizes[size] << "\n";
        }
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (proChosen == -1)
        {
            return false;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << "ERROR - SELECT A VALID ID\n\n";
            continue;
        }
        
        if (productInStock[proChosen][sizeChosen]>0)
        {
            char r;
            std::cout << "We have the product in Stock. Do you want to ship it? (y-yes, n-no)\n";
            std::cin >> r;
            
            if (r == 'y')
            {
                productInStock[proChosen][sizeChosen]--;
                productSent[proChosen][sizeChosen]++;
                
                std::cout << sizes[sizeChosen] << " " << products[proChosen] << " sent!\n\n";
                return true;
            }
            if (r == 'n')
            {
                return false;
            }
        }
        else
        {
            switch(proChosen)
            {
                case 0:
                case 1:
                case 2:
                    if (materialInStock[0][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[proChosen][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't have the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[0] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 3:
                    if (materialInStock[1][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[1][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[1][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[1] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 4:
                case 5:
                    if (materialInStock[2][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[2][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[2][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[2] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 6:
                    if (materialInStock[3][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[3][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[3][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[3] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 7:
                    if (materialInStock[4][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[4][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[4][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[4] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 8:
                case 9:
                    if (materialInStock[5][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[5][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[5][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[5] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 10:
                    if (materialInStock[6][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[6][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[6][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[6] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
                case 11:
                    if (materialInStock[7][sizeChosen]>0)
                    {
                        char r;
                        std::cout << "We have the material in Stock. Do you want to produce it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialInStock[7][sizeChosen]--;
                            productToCreate[proChosen][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << products[proChosen] << " was added to the products to create!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    else
                    {
                        char r;
                        std::cout << "We don't the material in Stock. Do you want to request it? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            materialToRequest[7][sizeChosen]++;
                            
                            std::cout << sizes[sizeChosen] << " " << materials[7] << " was added to the material to request!\n\n";
                            return true;
                        }
                        if (r == 'n')
                        {
                            return false;
                        }
                    }
                    break;
            }
        }
        return true;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    std::cout << "Welcome to Neist Point Management Bishes!\n";
    
    load_database();
    
    int val;
    do
    {
        std::cout << "1 - New Product request from costumer\n";
        // +materialToRequest OR +productToCreate
        
        std::cout << "2 - Material just ordered from Stanley\n";
        // -materialToRequest,  +materialShipping
        
        std::cout << "3 - Confirm Stanley material has arrived\n";
        // +materialInStock,   -materialShipping
        
        std::cout << "4 - Product left to be produced at Embroidery Sr. Luis.\n";
        //-materialInStock, +productToCreate
        
        std::cout << "5 - Confirm product from Embroidery Sr. Luis has arrived\n";
        //+productInStock,  -productToCreate
        
        // Show materialProduction matrix, ask if all was there?
        // If not, select individually which ones were done
        
        std::cout << "6 - Product is dispatched\n\n";
        //-productInStock, +productSold
        
        std::cout << "11 - See Materials to be requested to Stanley\n";
        std::cout << "12 - See Materials being shipped\n";
        std::cout << "13 - See Materials in Stock\n";
        std::cout << "14 - See Products to be created at Sr. Luis\n";
        std::cout << "15 - See Materials being transformed to Products\n";
        std::cout << "16 - See Products in Stock\n";
        std::cout << "17 - See Products sold\n\n";
        
        std::cout << "0 - QUIT. For that reason, I'm out!\n";
        
        std::cout << "What can I do for you today sir?\n";
        
        std::cout << "\n";
        std::cin >> val;
        
        switch(val)
        {
            case 1: if (new_product())
                    {
                        save_database();
                    }
                    break;
            case 2: order_material();
                    save_database();
                    break;
            case 3: if (material_arrived())
                    {
                       save_database();
                    }
                    break;
            case 4: if (order_product())
                    {
                        save_database();
                    }
                    break;
            case 5: if (product_arrived())
                    {
                        save_database();
                    }
                    break;
            case 6: if (product_dispatched())
                    {
                        save_database();
                    }
                    break;
                
            case 11: show_material2request();
                     break;
            case 12: show_materialShipping();
                     break;
            case 13: show_materialStock();
                     break;
            case 14: show_product2create();
                     break;
            case 15: show_productCreating();
                     break;
            case 16: show_productStock();
                     break;
            case 17: show_productSent();
                     break;
                
            default: break;
        }
    } while (val != 0);
    
    return 0;
}
*/
