# CTFs
A slowly growing collection of CTFs written by me.
(Contributors will be placed in contributors.md)

Don't you know CTFs? [Take a look here](https://en.wikipedia.org/wiki/Capture_the_flag#Computer_security)

## Let's start H4ck1ng!

1. Open `Challenges` folder.
2. Choose the type of CTF.
3. Choose your difficulty. Open folder `easy`, `medium` or `hard`.
4. Choose the type of challenge (`web`,`crypto`,`pwn`,`reversing`, ... ).
5. Open `description.md` and find instructions to build or compile the challenge.
6. Then open ONLY the `dist` folder. (Only the `dist` folder files are given to the challenger).


## Flag format
Flags matches regex: `CTF\{[0-9A-Za-z\_]+\}`

#### Directories structure

* The user should only open `dist` folder.
* `src` folder contains files to create the challenge.
* `service` folder contains files that should remain hidden to the user.
* `docker_scratches` contains some sample scratches to create challenges with docker


```
.
├── Challenges
│   ├── ....
│   └── CTF TYPE
│       ├── DIFFICULTY
│       │   ├── CHALLENGE TYPE
│       │   │   └── CHALLENGE
│       │   │       ├── dist
│       │   │       │   ├── FILE 1
│       │   │       │   ├── ...
│       │   │       │   └── FILE n
│       │   │       ├── service
│       │   │       │   ├── FILE 1
│       │   │       │   ├── ...
│       │   │       │   └── FILE n
│       │   │       └── src
│       │   │           ├── FILE 1
│       │   │           ├── ...
│       │   │           └── FILE n
│       │   └── ....
│       └── ....
├── docker_scratches
│   └── TYPE OF SCRATCH
│       └── ...
├── LICENSE
└── README.md
```
