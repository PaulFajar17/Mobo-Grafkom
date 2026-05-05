#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <model.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// toggles
bool pointLightOn = true;
bool spotLightOn = true;
bool lKeyPressed = false;
bool kKeyPressed = false;

// info toggles
bool showingInfo1 = false;
bool showingInfo2 = false;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tugas Akhir - Virtual Exhibition Room", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("src/shaders/tugas_akhir.vs", "src/shaders/tugas_akhir.fs");

    // load models
    // -----------
    Model model1("resources/objects/motherboard-components.glb");
    Model model2("resources/objects/motherboard__components.glb");
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // A large cube for the room (normals point inwards)
    float roomVertices[] = {
        // positions          // normals           // texture coords
        // Back face (z = -15)
        -15.0f,  0.0f, -15.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // Bottom-left
         15.0f, 10.0f, -15.0f,  0.0f,  0.0f,  1.0f, 10.0f, 10.0f, // top-right
         15.0f,  0.0f, -15.0f,  0.0f,  0.0f,  1.0f, 10.0f, 0.0f, // bottom-right         
         15.0f, 10.0f, -15.0f,  0.0f,  0.0f,  1.0f, 10.0f, 10.0f, // top-right
        -15.0f,  0.0f, -15.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
        -15.0f, 10.0f, -15.0f,  0.0f,  0.0f,  1.0f,  0.0f, 10.0f, // top-left
        // Front face (z = 15)
        -15.0f,  0.0f,  15.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
         15.0f,  0.0f,  15.0f,  0.0f,  0.0f, -1.0f, 10.0f, 0.0f, // bottom-right
         15.0f, 10.0f,  15.0f,  0.0f,  0.0f, -1.0f, 10.0f, 10.0f, // top-right
         15.0f, 10.0f,  15.0f,  0.0f,  0.0f, -1.0f, 10.0f, 10.0f, // top-right
        -15.0f, 10.0f,  15.0f,  0.0f,  0.0f, -1.0f,  0.0f, 10.0f, // top-left
        -15.0f,  0.0f,  15.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
        // Left face (x = -15)
        -15.0f, 10.0f,  15.0f,  1.0f,  0.0f,  0.0f, 10.0f, 10.0f, // top-right
        -15.0f, 10.0f, -15.0f,  1.0f,  0.0f,  0.0f,  0.0f, 10.0f, // top-left
        -15.0f,  0.0f, -15.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
        -15.0f,  0.0f, -15.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
        -15.0f,  0.0f,  15.0f,  1.0f,  0.0f,  0.0f, 10.0f, 0.0f, // bottom-right
        -15.0f, 10.0f,  15.0f,  1.0f,  0.0f,  0.0f, 10.0f, 10.0f, // top-right
        // Right face (x = 15)
         15.0f, 10.0f,  15.0f, -1.0f,  0.0f,  0.0f, 10.0f, 10.0f, // top-left
         15.0f,  0.0f, -15.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
         15.0f, 10.0f, -15.0f, -1.0f,  0.0f,  0.0f,  0.0f, 10.0f, // top-right         
         15.0f,  0.0f, -15.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
         15.0f, 10.0f,  15.0f, -1.0f,  0.0f,  0.0f, 10.0f, 10.0f, // top-left
         15.0f,  0.0f,  15.0f, -1.0f,  0.0f,  0.0f, 10.0f, 0.0f, // bottom-left     
        // Bottom face (y = 0)
        -15.0f,  0.0f, -15.0f,  0.0f,  1.0f,  0.0f,  0.0f, 10.0f, // top-right
         15.0f,  0.0f, -15.0f,  0.0f,  1.0f,  0.0f, 10.0f, 10.0f, // top-left
         15.0f,  0.0f,  15.0f,  0.0f,  1.0f,  0.0f, 10.0f, 0.0f, // bottom-left
         15.0f,  0.0f,  15.0f,  0.0f,  1.0f,  0.0f, 10.0f, 0.0f, // bottom-left
        -15.0f,  0.0f,  15.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-right
        -15.0f,  0.0f, -15.0f,  0.0f,  1.0f,  0.0f,  0.0f, 10.0f, // top-right
        // Top face (y = 10)
        -15.0f, 10.0f, -15.0f,  0.0f, -1.0f,  0.0f,  0.0f, 10.0f, // top-left
         15.0f, 10.0f,  15.0f,  0.0f, -1.0f,  0.0f, 10.0f, 0.0f, // bottom-right
         15.0f, 10.0f, -15.0f,  0.0f, -1.0f,  0.0f, 10.0f, 10.0f, // top-right     
         15.0f, 10.0f,  15.0f,  0.0f, -1.0f,  0.0f, 10.0f, 0.0f, // bottom-right
        -15.0f, 10.0f, -15.0f,  0.0f, -1.0f,  0.0f,  0.0f, 10.0f, // top-left
        -15.0f, 10.0f,  15.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f  // bottom-left        
    };
    
    // A simple cube for tables (normals pointing outwards)
    float cubeVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    // Room VAO
    unsigned int roomVBO, roomVAO;
    glGenVertexArrays(1, &roomVAO);
    glGenBuffers(1, &roomVBO);
    glBindVertexArray(roomVAO);
    glBindBuffer(GL_ARRAY_BUFFER, roomVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roomVertices), roomVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Cube/Table VAO
    unsigned int cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Lighting setup
    glm::vec3 pointLightPos(0.0f, 9.0f, 0.0f);
    glm::vec3 model1Pos(-6.0f, 1.55f, 0.0f);
    glm::vec3 model2Pos(6.0f, 1.55f, 0.0f);
    
    glm::vec3 spotlight1Pos(-6.0f, 8.0f, 0.0f);
    glm::vec3 spotlight1Dir(0.0f, -1.0f, 0.0f); // Pointing down
    
    glm::vec3 spotlight2Pos(6.0f, 8.0f, 0.0f);
    glm::vec3 spotlight2Dir(0.0f, -1.0f, 0.0f); // Pointing down

    ourShader.use();
    ourShader.setInt("material.texture_diffuse1", 0);
    ourShader.setInt("material.texture_specular1", 1);
    ourShader.setFloat("material.shininess", 32.0f);

    // Create a 1x1 white texture for objects without textures (room, tables)
    unsigned int whiteTexture;
    glGenTextures(1, &whiteTexture);
    glBindTexture(GL_TEXTURE_2D, whiteTexture);
    unsigned char whiteData[] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Create a 1x1 dark gray texture for tables
    unsigned int grayTexture;
    glGenTextures(1, &grayTexture);
    glBindTexture(GL_TEXTURE_2D, grayTexture);
    unsigned char grayData[] = { 70, 70, 70, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, grayData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Camera constraints (don't go out of the room)
        if (camera.Position.x < -14.0f) camera.Position.x = -14.0f;
        if (camera.Position.x >  14.0f) camera.Position.x =  14.0f;
        if (camera.Position.z < -14.0f) camera.Position.z = -14.0f;
        if (camera.Position.z >  14.0f) camera.Position.z =  14.0f;
        camera.Position.y = 1.8f; // Standard walking height

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        
        // Passing light toggles
        ourShader.setBool("pointLightOn", pointLightOn);
        ourShader.setBool("spotLightOn", spotLightOn);

        // Point light (ceiling)
        ourShader.setVec3("pointLight.position", pointLightPos);
        ourShader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
        ourShader.setVec3("pointLight.diffuse", 1.0f, 1.0f, 1.0f); // White light
        ourShader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
        ourShader.setFloat("pointLight.constant", 1.0f);
        ourShader.setFloat("pointLight.linear", 0.09f);
        ourShader.setFloat("pointLight.quadratic", 0.032f);

        // Spotlight 1 (Model 1)
        ourShader.setVec3("spotLight1.position", spotlight1Pos);
        ourShader.setVec3("spotLight1.direction", spotlight1Dir);
        ourShader.setVec3("spotLight1.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight1.diffuse", 1.0f, 0.8f, 0.0f); // Yellow light
        ourShader.setVec3("spotLight1.specular", 1.0f, 0.8f, 0.0f);
        ourShader.setFloat("spotLight1.constant", 1.0f);
        ourShader.setFloat("spotLight1.linear", 0.09f);
        ourShader.setFloat("spotLight1.quadratic", 0.032f);
        ourShader.setFloat("spotLight1.cutOff", glm::cos(glm::radians(12.5f)));
        ourShader.setFloat("spotLight1.outerCutOff", glm::cos(glm::radians(15.0f)));
        
        // Spotlight 2 (Model 2)
        ourShader.setVec3("spotLight2.position", spotlight2Pos);
        ourShader.setVec3("spotLight2.direction", spotlight2Dir);
        ourShader.setVec3("spotLight2.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight2.diffuse", 1.0f, 0.8f, 0.0f); // Yellow light
        ourShader.setVec3("spotLight2.specular", 1.0f, 0.8f, 0.0f);
        ourShader.setFloat("spotLight2.constant", 1.0f);
        ourShader.setFloat("spotLight2.linear", 0.09f);
        ourShader.setFloat("spotLight2.quadratic", 0.032f);
        ourShader.setFloat("spotLight2.cutOff", glm::cos(glm::radians(12.5f)));
        ourShader.setFloat("spotLight2.outerCutOff", glm::cos(glm::radians(15.0f)));

        ourShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Render Room (No texture applied for simplicity, relying on minimal ambient and lights)
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, whiteTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, whiteTexture);

        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        glBindVertexArray(roomVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render Tables (Using basic cubes)
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grayTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, grayTexture);

        // Table 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-6.0f, 0.75f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.5f, 2.0f)); // Table dimensions
        ourShader.setMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Table 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(6.0f, 0.75f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.5f, 2.0f));
        ourShader.setMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render 3D Models
        // Model 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, model1Pos);
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));	
        ourShader.setMat4("model", model);
        model1.Draw(ourShader);
        
        // Model 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, model2Pos);
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        // Rotate the second one to look different
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);
        model2.Draw(ourShader);
        
        // Distance Detection Logic
        float dist1 = glm::distance(camera.Position, model1Pos);
        if (dist1 < 3.5f && !showingInfo1) {
            std::cout << "\n===================================" << std::endl;
            std::cout << "Motherboard 1: ASUS ROG Maximus" << std::endl;
            std::cout << "Chipset: Z790" << std::endl;
            std::cout << "Socket: LGA 1700" << std::endl;
            std::cout << "===================================" << std::endl;
            showingInfo1 = true;
        } else if (dist1 >= 3.5f) {
            showingInfo1 = false;
        }

        float dist2 = glm::distance(camera.Position, model2Pos);
        if (dist2 < 3.5f && !showingInfo2) {
            std::cout << "\n===================================" << std::endl;
            std::cout << "Motherboard 2: MSI MAG B650 Tomahawk" << std::endl;
            std::cout << "Chipset: B650" << std::endl;
            std::cout << "Socket: AM5" << std::endl;
            std::cout << "===================================" << std::endl;
            showingInfo2 = true;
        } else if (dist2 >= 3.5f) {
            showingInfo2 = false;
        }

        // glfw: swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &roomVAO);
    glDeleteBuffers(1, &roomVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
        
    // Toggle Point Light ('L' key)
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !lKeyPressed) {
        pointLightOn = !pointLightOn;
        lKeyPressed = true;
        std::cout << "Point Light: " << (pointLightOn ? "ON" : "OFF") << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
        lKeyPressed = false;
    }

    // Toggle Spot Lights ('K' key)
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && !kKeyPressed) {
        spotLightOn = !spotLightOn;
        kKeyPressed = true;
        std::cout << "Spotlights: " << (spotLightOn ? "ON" : "OFF") << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
        kKeyPressed = false;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
