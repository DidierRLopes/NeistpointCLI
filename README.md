# neistpointTerminal
Neistpoint Stock Management Database

The aim of this program is to allow the clothing brand NeistPoint to manage their cloths stocks.
You can see more about the brand on their insta page: https://www.instagram.com/neistclothing/
or on their website: https://neistclothing.com

The menu of this program is shown below:
-------------------------------------------------------------------------
Welcome to Neist Point Management Database!
17 - See program flow

1 - New Product request from costumer

2 - Add Material to be requested
3 - See Materials to be requested
4 - Add Product to be created
5 - See Products to be created

6 - Order Material
7 - See Materials being shipped
8 - Confirm Material has arrived
9 - See Materials in stock
10 - See possible products to be created from material stock

11 - Order Products from Material stock
12 - See Products being created and shipped
13 - Confirm Product has arrived
14 - See Products in stock
15 - Product is dispatched
16 - See Products Sent

What can I do for you today? (0 - EXIT and SAVE)
-------------------------------------------------------------------------

Since the menu may be a little confusing, a draft of the program flow is availabe.
This can be seen below:

                  (request_material())                  
request_product() ------------------->   [materialToRequest] 
                      |                           | 
                      |                           |  order_material()  
                      |                           V 
                      |                   [materialShipping]    
                      |                           | 
                      |                           |  arrived_material()  
                      |                           V 
                      |                   [materialInStock]  ----  
                      |                                         | 
                      |                                         | 
                      ----------------->  [productToCreate]     | 
                     (request_product())          |             V 
                                                  |  order_product()  
                                                  V 
                                          [productCreating]    
                                                 | 
                                                 |  arrived_product()  
                                                 V 
                                           [productInStock]    
                                                 | 
                                                 |  sent_product()  
                                                 V 
                                            [productSent]   

-------------------------------------------------------------------------

In addition, the "NeistPoint_database.csv" file will be always updated with all the matrices. 
