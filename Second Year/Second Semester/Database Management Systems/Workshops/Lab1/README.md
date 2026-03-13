# Lab-1 SGBD

## Configuration for the database
1. Open the application **pgAdmin 4**
2. Open the **Server** tab
3. Open the **Databases** tab
4. Create a new database and give it a name

## Configuration the connection to the database
1. Inserting the dependencies in build.gradle **implementation 'org.postgresql:postgresql:42.7.3'**
2. Use the Database icon of the IntelliJ IDEA to open the connection menu
3. Create a new connection using the **+** button, select **Data Source** and select **PostgreSQL**
4. Fill the fields with the information of **user**, **password** and **database**
5. Test the connection, and if everything is ok, click **APPLY** and **OK**
6. To test it in the IntelliJ IDEA try to make a connection to the database using the **DriverManager.getConnection** method