# Documentation

## Table of Contents

1. <u>Core</u>

    * [Engine class](#engine-class)

1. <u>Camera</u>
    
    * [Camera class](#camera-class)

1. <u>Graphics</u>

    * [TextureManager class](#texturemanager-class)

    * [Animation class](#animation-class)

1. <u>Inputs</u>

    * [Input class](#input-class)

1. <u>Game Objects</u>

    * [IObject Interface](#iobject-interface)

    * [Properties struct](#properties-struct)

    * [GameObject class](#gameobject-class)

    * [Character class](#character-class)

1. <u>Colliders</u>

    * [Collider class](#collider-class)

    * [BoxCollider class](#boxcollider-class)



## 1. <u>Core</u>

- ### Engine class

    ### <u>Members</u>
    ---

    **Private :**
    *   `bool m_IsRunning` : Used to control the running state of the main loop.

    *   `static Engine* s_Instance` :  Only instance of the Engine class following the singleton pattern.  

    *   `SDL_Renderer* m_Renderer` : SDL Renderer used to render textures on the screen.  

    *   `SDL_Window* m_Window` : An SDL Window used as the main window of the application.  

    *   `GameMap* m_LevelMap` : A GameMap Object used to represent the current level Tile Map.

    ### <u>Methods</u>
    ---

    * `static Engine* GetInstance()` : Statis getter for the only Engine instance. Follows the singleton pattern.

    *   ` void Init()` : Initializes the engine, this method is responsible for initialising all the necessary components before the the attribute `m_IsRunning` is set to `true`. In this function you should initialize SDL components (`SDL_Init`, Window, Renderer, ...), Initialize the Texture Manager and create the components you need to be presents when the Engine starts. You should also handle the change of the attribute `m_IsRunning` in this method.

        <u>Exemple :</u> 
        ```c++
            void Engine::Init() {

            m_IsRunning = false;

            if (!SDL_Init(SDL_INIT_VIDEO)) {
                SDL_Log("Failed to init SDL: %s", SDL_GetError());
                SDL_Quit();
                return;
            }

            SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
            m_Window = SDL_CreateWindow("Engine", SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
            if (m_Window == nullptr) {
                SDL_Log("Failed to create window : %s", SDL_GetError());
                SDL_Quit();
                return;
            }

            m_Renderer = SDL_CreateRenderer(m_Window, NULL);
            if (!m_Renderer) {
                SDL_Log("Failed to create Renderer : %s", SDL_GetError());
                SDL_Quit();
                return;
            }

            if(!MapParser::GetInstance()->Load("level1", "/Path/to/your/assets/maps/level1.tmj")) {
                std::cout << "Failed to load map" << std::endl;
            }

            m_LevelMap = MapParser::GetInstance()->GetMap("level1");

            TextureManager::GetInstance()->Load("playerIdle", "/Path/to/your/assets/player/Idle32.png");
            TextureManager::GetInstance()->Load("playerRun", "/Path/to/your/assets/player/Run32.png");
            
            player = new Warrior(new Properties("playerRun", SCREEN_WIDTH/2, 0, 32, 32));
            player->AddCollider<class BoxCollider>(player->GetOrigin(), 32, 32);

            Camera::GetInstance()->SetTarget(player->GetOrigin());
            m_IsRunning = true;
        }
        ```

    * `void Clean()` : Calls the cleaner function of the Texture manager and handles the cleaning of SDL Objects (Destroys Window and Renderer). Properly quits SDL with `SDL_Quit()`.

    * `void Quit()` : Sets `m_IsRunning` to `false`.

    **The next 3 methods should be called continuously while the main loop is active :**

    * `void Update()` : This method should be called continuously while the mainloop is active. You should call every Object's `Update()` method in this method. This method should also handle the DeltaTime calculation if needed.

        <u>Exemple :</u>
        ```c++
        void Engine::Update() {
            float dt = Timer::GetInstance()->GetDeltaTime();
            m_LevelMap->Update();
            player->Update(dt);
            Camera::GetInstance()->Update(dt);
        }
        ```

    * `void Render()` : This method should be called continuously while the mainloop is active. You should call every Object's `Render()` or equivalent method in this method.

        <u>Exemple :</u>
        ```c++
        void Engine::Render() {
            SDL_SetRenderDrawColor(m_Renderer, 255, 236, 161, 255);
            SDL_RenderClear(m_Renderer);

            m_LevelMap->Render();
            player->Draw();
            SDL_RenderPresent(m_Renderer);
        }
        ```

    * `void Events()` : Handles event listening. Particularly used for input handling. This method should be called continuously while the mainloop is active. 

    * `bool isRunning()` : Getter for the `m_IsRunning` member.

    * `SDL_Renderer* GetRenderer()` : Getter for the `m_Renderer` member.

## 2. <u>Camera</u>

- ### Camera class

    ### <u>Members</u>
    ---

    **Private :**

    * `static Camera* s_Instance` : Unique instance of the Camera class. Following the singleton patern.

    * `SDL_FRect m_ViewBox` : SDL_FRect representing the view port of the Camera. This is set to `{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}` by default by the constructor.

    * `Vector2D m_Position` : Current position of the Camera.

    * `Vector2D* m_Target` : References the position of target Object to follow. 

    ### <u>Methods</u>
    ---

    **Private :**

    * `static Camera* GetInstance()` : Getter for the unique and private instance of the Camera Class. Follows the singleton pattern.

    * `SDL_FRect GetViewBox()` : Getter for the m_ViewBox member.

    * `Vector2D GetPosition()` : Getter for the m_Position member.

    * `void SetTarget(Vector2D* target)` : Setter for the m_Target member.

    * `void Update(float dt)` : Used to Update the Camera position to follow the `m_Target` position. Put this in the `Update()` method of the Engine.

## 3. <u>Graphics</u>

- ### TextureManager class

    ### <u>Members</u>
    ---

    **Private :**

    * `static TextureManager* s_Instance` : Unique instance of the Texture Manager class, following the singleton pattern.

    * `std::map<std::string, SDL_Texture*> m_TextureMap` : Contains the list of all textures (SDL_Texture) identified by an id (of type std::string) and stored in a std::map structure.

    ### <u>Methods</u>
    ---

    * `static TextureManager* GetInstance()` : Getter for the unique instance of the class. Follows the singleton pattern.

    * `bool Load(std::string id, std::string filename)` : Loads an image file as a texture (using SDL_Surface and SDL_CreateTextureFromSurface) and stores it in `m_TextureMap` member.

    * `void Drop(std::string id)` : Destroys the corresponding texture in the `m_TextureMap` structure and erases it from the map.

    * `void Draw(std::string id, float x, float y, float width, float height, SDL_FlipMode flip=SDL_FLIP_NONE)` : Draws the texture corresponding to `id` in `m_TextureMap` at the position `(x,y)` on the screen. `width` and `height` should correspond to the source image of the Texture.

    * `void DrawTile(std::string tilesetID, float x, float y, float tileSize, int row, int frame, SDL_FlipMode flip=SDL_FLIP_NONE)` : Draws the Texture of a Tile on the screen in the same way as Draw but uses paramters `row` and `frame` to render a specific Tile from a tileset.

    * `void DrawFrame(std::string id, float x, float y, float widht, float height, int row, int frame, SDL_FlipMode flip=SDL_FLIP_NONE)` : Draws the Texture of a Frame on the screen in the same way as DrawTile, using `row`and `frame`to specifiy the position on a frameset.

    * `void Clean()` : Cleans the `m_TextureMap` by destroying every SDL_Texture and clearing `m_TextureMap`.
    ---

- ### Animation class

    ### <u>Members</u>

    ---

    **Private :**

    * `int m_SpriteRow` : Row index in the spritesheet corresponding to the animation.
    * `std::string m_TextureID` : ID of the texture used (referenced from the `TextureManager`).
    * `int m_FrameCount` : Total number of frames in the animation.
    * `int m_AnimSpeed` : Animation speed (delay between two frames).
    * `int m_SpriteFrame` : Current frame index of the animation (progresses over time).
    * `SDL_FlipMode m_Flip` : Flip mode for rendering (`SDL_FLIP_NONE`, `SDL_FLIP_HORIZONTAL`, `SDL_FLIP_VERTICAL`).

    ---

    ### <u>Methods</u>

    ---

    * `Animation()` : Default constructor. Initializes an empty animation.

    * `void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_FlipMode flip = SDL_FLIP_NONE)` :
    Sets the animation properties:

    * `textureID` : ID of the texture (managed by `TextureManager`).
    * `spriteRow` : The row of the spritesheet containing the animation.
    * `frameCount` : Total number of frames for the animation.
    * `animSpeed` : Speed of the animation (time interval between frame changes).
    * `flip` : Optional flip mode (horizontal/vertical mirroring).

    * `void Update()` : Updates the current state of the animation. Advances `m_SpriteFrame` based on the animation speed (`m_AnimSpeed`) and elapsed time. Should be called in the `Update()` method of the GameObject tied to this Animation.

    * `void Draw(float x, float y, int spriteWidth, int spriteHeight)` : Renders the current animation frame at position `(x, y)` on the screen, with dimensions `spriteWidth` and `spriteHeight`. Uses `m_TextureID`, `m_SpriteRow`, `m_SpriteFrame`, and `m_Flip` to select and draw the correct frame from the spritesheet.

        **Exemple of usage :**
        ```c++
        #ifndef WARRIOR_H
        #define WARRIOR_H

        #include "Character.h"
        #include "Animation.h"
        #include "RigidBody.h" 

        class Warrior: public Character{
            public:
                Warrior(Properties* props);

                virtual void Draw();
                virtual void Update(float dt);
                virtual void Clean();

                inline void SetFlipState(bool state) {m_HasFlipped = state;}
                inline bool GetFlipState() {return m_HasFlipped;}

            private:
                Animation* m_Animation; //Add an Animation Component
                RigidBody* m_RigidBody;
                bool m_HasFlipped;
        };

        #endif
        ```
        ```c++
            void Warrior::Update(float dt) {
            GetFlipState() ? m_Animation->SetProps("playerIdle", 1, 11, 80, SDL_FLIP_HORIZONTAL) : m_Animation->SetProps("playerIdle", 1, 11, 80); // Sets an Animation to play 
            m_RigidBody->UnsetForce();

            if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
                m_Animation->SetProps("playerRun", 1, 12, 80, SDL_FLIP_HORIZONTAL); // Use the SetProps method to change the animation according to certain events
                m_RigidBody->ApplyForceX(-15);
                SetFlipState(true);
            }

            if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
                m_Animation->SetProps("playerRun", 1, 12, 80); // Change the flip
                m_RigidBody->ApplyForceX(15);
                SetFlipState(false);
            }
            m_Animation->Update();
        }
        ```
    ---

## 4. <u>Inputs</u>

- ### Input class

    ### <u>Members</u>

    ---

    **Private :**

    * `const bool* m_KeyStates` : Pointer to the array of keyboard states managed by SDL. Each element corresponds to a specific key (indexed by `SDL_Scancode`), with `true` meaning the key is currently pressed.

    * `static Input* s_Instance` : Unique instance of the Input class, implementing the singleton pattern.

    ---

    ### <u>Methods</u>

    ---

    * `static Input* GetInstance()` : Getter for the unique instance of the class. Creates it if it does not already exist (singleton pattern).

    * `Input()` : Private constructor. Initializes the `m_KeyStates` pointer by calling `SDL_GetKeyboardState()`.

    * `void Listen()` : Processes SDL events using `SDL_PollEvent`. Handles the following by default:

    * `SDL_EVENT_QUIT` : Calls `Engine::GetInstance()->Quit()` to exit the application.
    * `SDL_EVENT_KEY_DOWN` : Updates the keyboard states via `KeyDown()`.
    * `SDL_EVENT_KEY_UP` : Updates the keyboard states via `KeyUp()`.

    * `bool GetKeyDown(SDL_Scancode key)` : Checks whether the specified key (identified by its `SDL_Scancode`) is currently pressed. Returns `true` if the key is down, `false` otherwise.
        
        **Usage exemple :**
        ```c++
            void Warrior::Update(float dt) {
                // Checks if the A key is pressed to move and set Animation accordingly
                if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
                    m_Animation->SetProps("playerRun", 1, 12, 80, SDL_FLIP_HORIZONTAL);
                    m_RigidBody->ApplyForceX(-15);
                    SetFlipState(true);
                }
                // Checks is D key is pressed for the other side.
                if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
                    m_Animation->SetProps("playerRun", 1, 12, 80);
                    m_RigidBody->ApplyForceX(15);
                    SetFlipState(false);
                }

                m_RigidBody->Update(dt);
                m_Animation->Update();
        }
        ```

    * `void KeyUp()` : Refreshes the keyboard state after a key release event by calling `SDL_GetKeyboardState()`.

    * `void KeyDown()` : Refreshes the keyboard state after a key press event by calling `SDL_GetKeyboardState()`.

    ---

## 5. <u>Game Objects</u>

- ### IObject Interface

    ### <u>Methods</u>

    ---

    * `virtual void Draw() = 0` : Pure virtual method. Must be implemented by derived classes to render the object on the screen.

    * `virtual void Update(float dt) = 0` : Pure virtual method. Must be implemented by derived classes to update the object’s state each frame. `dt` is the delta time (time elapsed since the last frame).

    * `virtual void Clean() = 0` : Pure virtual method. Must be implemented by derived classes to clean up and release the object’s resources.

    ---

- ### Properties struct

    To set a Game Object's attributes (width, height, textureID, ...) a Properties struct is passed to the GameObject's Constructor. 

    ### <u>Members</u>

    ---

    * `float x, y` : Initial position of the object in world coordinates.

    * `int Width, Height` : Dimensions of the object’s sprite in pixels.

    * `std::string textureID` : Identifier of the texture used to render the object (linked with the `TextureManager`).

    * `SDL_FlipMode Flip` : Flip mode used when rendering (`SDL_FLIP_NONE`, `SDL_FLIP_HORIZONTAL`, `SDL_FLIP_VERTICAL`).

    ---

    ### <u>Methods</u>

    ---

    * `Properties(std::string TextureID, int X, int Y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE)` :
    Constructor. Initializes a set of properties to create a `GameObject`.

    * `TextureID` : ID of the texture.
    * `X`, `Y` : Starting position of the object.
    * `width`, `height` : Sprite dimensions.
    * `flip` : Optional, defines whether the sprite is flipped on render.

        **Exemple :**

        ```c++
            struct Properties {
            public: 
                float x, y;
                int Width, Height;
                std::string textureID;
                SDL_FlipMode Flip;

                Properties(std::string TextureID, int X, int Y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE) {
                    x = X;
                    y = Y;
                    Flip = flip;
                    Width = width;
                    Height = height;
                    textureID = TextureID; 
                }
        };
        ```

---

- ### GameObject class

    ### <u>Members</u>

    ---

    **Protected :**

    * `Vector2D* m_Origin` : Represents the center point of the GameObject, used for transformations and rotations.

    * `Transform* m_Transform` : Transform Object holding information about the Object's position and used to move it in the scene.

    * `Collider* m_Collider` : Pointer to a Collider object associated with the GameObject, used for collision detection.

    * `int m_Width, m_Height` : Dimensions (in pixels) of the GameObject.

    * `std::string m_TextureID` : Identifier of the texture used for rendering the GameObject (referenced from the `TextureManager`).

    * `SDL_FlipMode m_Flip` : Flip mode for rendering (`SDL_FLIP_NONE`, `SDL_FLIP_HORIZONTAL`, `SDL_FLIP_VERTICAL`).

    ---

    ### <u>Methods</u>

    ---

    * `GameObject(Properties* props)` : Constructor. Initializes the GameObject with the given properties (textureID, position, dimensions, flip mode... see [Properties struct](#properties-struct)). Also initializes `m_Transform` and calculates the object’s `m_Origin`.

    * `template<typename ColliderType, typename... Args> void AddCollider(Args&&... args)` : Adds a collider of type `ColliderType` to the GameObject. If a collider already exists, it is deleted and replaced.

    * `inline Vector2D* GetOrigin()` : Returns a pointer to the object’s origin (`m_Origin`).

    * `virtual void Draw() = 0` : Pure virtual method. Must be implemented by derived classes to render the object.

    * `virtual void Update(float dt) = 0` : Pure virtual method. Must be implemented by derived classes to update the object’s state each frame, based on `dt`.

    * `virtual void Clean() = 0` : Pure virtual method. Must be implemented by derived classes to release resources and clean memory.

    ---

- ### Character class

    ### <u>Members</u>

    ---

    **Protected :**

    * `std::string m_Name` : Name of the character, used for identification (e.g., player, enemy, NPC).

    ---

    ### <u>Methods</u>

    ---

    * `Character(Properties* props)` : Constructor. Calls the `GameObject` constructor to initialize position, dimensions, texture, and origin.

    * `virtual void Draw() = 0` : Pure virtual method. Must be implemented by derived classes to render the character on screen.

    * `virtual void Update(float dt) = 0` : Pure virtual method. Must be implemented by derived classes to update the character’s behavior and state each frame.

    * `virtual void Clean() = 0` : Pure virtual method. Must be implemented by derived classes to free resources and handle cleanup.

        **Exemple of Player class derived from Character class :**

        ```c++
        #include "Character.h"
        #include "Animation.h"
        #include "RigidBody.h" 

        class Player: public Character{
            public:
                Player(Properties* props);

                virtual void Draw();
                virtual void Update(float dt);
                virtual void Clean();

                inline void SetFlipState(bool state) {m_HasFlipped = state;}
                inline bool GetFlipState() {return m_HasFlipped;}

            private:
                Animation* m_Animation;
                RigidBody* m_RigidBody;
                bool m_HasFlipped;
        };
        ```
        And create the instance in `Init()` method of the Engine :
        ```c++
            player = new Player(new Properties("playerRun", SCREEN_WIDTH/2, 0, 32, 32));
            player->AddCollider<class BoxCollider>(player->GetOrigin(), 32, 32);

            Camera::GetInstance()->SetTarget(player->GetOrigin());
        ```
---

## 6. <u>Colliders</u>

- ### Collider class

    ### <u>Members</u>

    ---

    **Protected :**

    * `Vector2D* m_Target` : Pointer to the target’s position vector. The collider tracks this target to stay aligned with the object it belongs to.

    * `Vector2D m_Position` : Internal position of the collider, updated from the target each frame.

    ---

    ### <u>Methods</u>

    ---

    * `Collider(Vector2D* target)` : Constructor. Initializes the collider at the target’s position.

    * `virtual ~Collider() = default` : Virtual destructor. Ensures proper cleanup when derived colliders are destroyed.

    * `inline void Update()` : Updates the collider’s position based on its target and recalculates its axes and vertices (calls `UpdateAxesAndVertices()`).

    * `virtual void UpdateAxesAndVertices() = 0` : Pure virtual method. Must be implemented in derived classes to compute the collider’s vertices and axes (used in collision detection).

    * `virtual void ProjectOnAxis(const Vector2D& axis, float& min, float& max) const = 0` : Pure virtual method. Projects the collider onto a given axis (used in the Separating Axis Theorem).

    * `virtual bool isOverlapped(const Collider& other) const = 0` : Pure virtual method. Checks if this collider overlaps with another collider (general collision check).

    * `virtual bool isOverlappedWithBox(const class BoxCollider& box) const = 0` : Pure virtual method. Double dispatch method for handling overlap checks specifically with a `BoxCollider`.

    * `virtual std::vector<Vector2D> GetAxes() const = 0` : Returns the list of axes relevant for collision detection.

    * `virtual std::vector<Vector2D> GetVertices() const = 0` : Returns the list of vertices defining the collider’s shape.

    * `inline const Vector2D& GetPosition() const` : Returns the current position of the collider.

    ---

- ### BoxCollider class

    ### <u>Members</u>

    ---

    **Private :**

    * `float m_Width, m_Height` : Dimensions of the box collider.

    * `std::vector<Vector2D> m_Axes` : List of axes used for collision detection (derived from the box’s edges).

    * `std::vector<Vector2D> m_Vertices` : List of the box’s corner points in world coordinates.

    ---

    ### <u>Methods</u>

    ---

    * `BoxCollider(Vector2D* target, float width, float height)` : Constructor. Creates a box collider aligned with the target position and sized by `width` and `height`.

    * `void UpdateAxesAndVertices() override` : Recalculates the vertices and axes of the box collider whenever its position is updated.

    * `void ProjectOnAxis(const Vector2D& axis, float& min, float& max) const override` : Projects the box collider onto the specified axis (used in collision detection via the Separating Axis Theorem).

    * `bool isOverlapped(const Collider& other) const override` : Checks whether this box collider overlaps with another collider, using double dispatch to determine the correct overlap logic.

    * `bool isOverlappedWithBox(const class BoxCollider& box) const override` : Checks for overlap specifically between two box colliders.

    * `inline std::vector<Vector2D> GetVertices() const override` : Getter for `m_Vertices` member.

    * `inline std::vector<Vector2D> GetAxes() const override` : Getter for the `m_Axes` member.

    ---











