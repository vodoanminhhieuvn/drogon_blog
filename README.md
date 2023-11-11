# E-Learning Backend

The Blog Backend Drogon Project is a RESTful API that provides the backend for the Client App.

## Getting started

- **Drogon Framework:** Built on top of [Drogon](https://github.com/drogonframework/drogon), leveraging its features for high speed.
- **Simple Blogging:** Create, edit, and delete blog posts.

### To-Do

- [x] Authentication
- [x] Fully Migrated DB [link](https://github.com/tutorials24x7/blog-database-mysql)
- [ ] Validator and Error handling (Current handling is dog water)
- [ ] Nested comments
- [ ] Dockerize

### Available Endpoints

BASE_URL : localhost:3000

* `/auth/**` - Authentication endpoints
* `/me/**` - Users endpoints
* `/posts/**` - Posts endpoints
* `/Comments/**` - Comments endpoints
* `/Categories/**` - Categories endpoints

For more details you can import Blog.postman_collection.json into Postman.

### Requirement

- C++2a
- Cmake 3.20.0
- Drogon 1.5.0
- PostgreSQL 16

### Setting up a project

1. Clone the repository:

    ```bash
    git clone https://github.com/vodoanminhhieuvn/drogon_blog.git
    ```

2. Build the project:

    ```bash
    cd drogon-blog
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the server:

    ```bash
    ./wblog
    ```

4. Open your Postman and navigate to `http://localhost:3000` to access the blog.


## Databases

### Initialize the database

Run [init.sql](/sql/init_schema.sql) to create the database and table

### Configure the database
By default, the project is configured to connect to PostgreSQL database.
You need to update your own [config.json](config.json) and [model.json](models/model.json) file to connect to your own database.

You want to create a new model, you can use the following command:

```bash
    drogon_ctl create model models
```

## Deployment (I don't know when it will be deployed because I'm broke :->)
