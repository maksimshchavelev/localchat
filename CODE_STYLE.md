

### 1. **Comment Formatting Rules:**

-   **Single-line comments** should follow the C-style format:  
    Example:
    
    ```cpp
    /* This is a single-line comment */
    ```
    
-   **Function, class, method, and file descriptions** must follow the **Doxygen** style. The comment max lenght must be limited to **100-110 characters**.
-   Every file should start with the **LICENSE's name and your username** (for example, `MIT LICENSE, Copyright (c) 2025, bob`)
-   Code examples can be included in descriptions, but **do not put examples in the `brief` or `detail` sections**.
-   Comments should be **clear**, **concise**, and **informative**.

----------

### 2. **Class, Method, and Function Naming Rules:**

-   **Class names** should be in **PascalCase** and should clearly reflect the purpose of the class. The name should not be too long or too short (e.g., not consisting of just 1-2 characters)
-   **Abbreviations and acronyms** should **not** be used in the names of classes, functions, and methods.
-   **Nested classes** (or internal utility ones) should start with an underscore (`_`) and follow **PascalCase**. However, **nested functions** and **methods** should start with an underscore and be in **snake_case**.
-   **Class fields** should be in **camelCase** and end with an underscore (`_`).
-   **Function or method argument names** should be meaningful, in **camelCase**, and indicate their type clearly.
-   **Template type names** should be meaningful and reflect their intended purpose.
-   **Method and function names** should be in **snake_case**.

----------

### 3. **Namespace Rules:**

-   Do not use namespaces, with the exception of **API** (for example, `api::chat_history` namespace means `/api/chat_history`)

----------

### 4. **Class or Struct?**

-   A **struct** should only contain **fields** or **types**. If it has methods (other than constructors or overloaded operators), it should be a **class**.
