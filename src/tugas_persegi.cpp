// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// stb_image.h definition already in other mains, but we need the functions 
// actually it's fine if we include it without defining implementation if done carefully, 
// but since this is a separate executable, we need STB_IMAGE_IMPLEMENTATION.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Set default mixValue (sesuaikan 6 dengan digit terakhir NIM Anda
// 240533609596)
float mixValue = 0.6f;

// Interaction states
glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
float objectScale = 1.0f;
float rotationSpeed = 1.0f;
glm::vec2 texOffset1 = glm::vec2(0.0f, 0.0f);
glm::vec2 texOffset2 = glm::vec2(0.0f, 0.0f);
glm::vec2 texScale1 = glm::vec2(1.0f, 1.0f);
glm::vec2 texScale2 = glm::vec2(1.0f, 1.0f);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Tugas Persegi - NIM", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  Shader ourShader("src/shaders/tugas_persegi.vs",
                   "src/shaders/tugas_persegi.fs");

  // Persegi menggunakan 2 Segitiga (EBO)
  float vertices[] = {
      // positions          // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // load textures
  unsigned int texture1, texture2;
  // texture 1 - profile.jpeg
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load("profile.jpeg", &width, &height, &nrChannels, 0);
  if (data) {
    float aspect = (float)width / height;
    if (aspect > 1.0f)
      texScale1 = glm::vec2(1.0f / aspect, 1.0f);
    else
      texScale1 = glm::vec2(1.0f, aspect);

    // Assume JPEG has 3 channels (GL_RGB)
    // If profile.jpeg actually has alpha, consider GL_RGBA. We use GL_RGB for
    // standard jpegs.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load profile.jpeg (texture 1)" << std::endl;
  }
  stbi_image_free(data);

  // texture 2 - nim.jpeg
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("nim.jpeg", &width, &height, &nrChannels, 0);
  if (data) {
    float aspect = (float)width / height;
    if (aspect > 1.0f)
      texScale2 = glm::vec2(1.0f / aspect, 1.0f);
    else
      texScale2 = glm::vec2(1.0f, aspect);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load nim.jpeg (texture 2)" << std::endl;
  }
  stbi_image_free(data);

  ourShader.use();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    ourShader.use();
    ourShader.setFloat("mixValue", mixValue);

    // Set offset for textures based on interactions
    glUniform2f(glGetUniformLocation(ourShader.ID, "offset1"), texOffset1.x,
                texOffset1.y);
    glUniform2f(glGetUniformLocation(ourShader.ID, "offset2"), texOffset2.x,
                texOffset2.y);

    // Set scale for textures to fix aspect ratios
    glUniform2f(glGetUniformLocation(ourShader.ID, "scale1"), texScale1.x,
                texScale1.y);
    glUniform2f(glGetUniformLocation(ourShader.ID, "scale2"), texScale2.x,
                texScale2.y);

    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),
                         (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

    // Model matrix with interactions
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, objectPos);
    model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed,
                        glm::vec3(0.5f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(objectScale, objectScale, objectScale));

    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);
    ourShader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // Dynamic mix value change
  // Using Up/Down Arrow keys to adjust mixValue
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    mixValue += 0.005f; // adjust speed appropriately
    if (mixValue >= 1.0f)
      mixValue = 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    mixValue -= 0.005f;
    if (mixValue <= 0.0f)
      mixValue = 0.0f;
  }

  // Translation (W, A, S, D)
  float moveSpeed = 0.01f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    objectPos.y += moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    objectPos.y -= moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    objectPos.x -= moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    objectPos.x += moveSpeed;

  // Scaling (E, Q)
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    objectScale += 0.01f;
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    objectScale -= 0.01f;
    if (objectScale < 0.1f)
      objectScale = 0.1f;
  }

  // Rotation Speed (Right, Left)
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    rotationSpeed += 0.01f;
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    rotationSpeed -= 0.01f;

  // Texture 1 Offset (I, J, K, L) - Untuk Profile
  float texSpeed = 0.005f;
  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    texOffset1.y -= texSpeed;
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    texOffset1.y += texSpeed;
  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    texOffset1.x += texSpeed;
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    texOffset1.x -= texSpeed;

  // Texture 2 Offset (T, F, G, H) - Untuk NIM
  if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    texOffset2.y -= texSpeed;
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    texOffset2.y += texSpeed;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    texOffset2.x += texSpeed;
  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    texOffset2.x -= texSpeed;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
