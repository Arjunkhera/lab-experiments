## General Instructions

This website is a singular project covering all web related experiments.  
**Prerequisites: Have nodejs installed**

## How to run

**Docker**

1. Install Docker
2. Change directory to Makefile
3. Type the following command to start the server

```bash
make run
```

**site runs at localhost:8080**

5. Type the following command to stop the server and delete the container

```bash
make clean
```

**Locally**

Enter the backend folder and run the following in the terminal
```bash
node app.js
```

or Alternatively


```bash
DEBUG=express-locallibrary-tutorial:* npm run start
```

**site runs at localhost:8080**

Pages **Under Development** are marked **UD**

1. The code structure of the website is as follows
    - index.html : landing page
    - rsa.html **[UD]**  : contains the form for second experiment
    - images     : contains the images
    - scripts    : js scripts
    - styles     : css and bootstrap
    - backend **[UD]**    : to done in django by @scipsycho, currently in nodejs
