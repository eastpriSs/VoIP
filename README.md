# VoIP Application Project 📞
The VoIP Application Project is a comprehensive solution for voice over internet protocol (VoIP) communications, providing a robust and feature-rich platform for users to make and receive calls. This project aims to deliver a high-quality, reliable, and scalable VoIP application that meets the needs of modern communication systems. 📈

## 🚀 Features
* User registration and authentication 📝
* Call initiation and management: hold call, voice off, disconnect 📞
* Recent call history and logging 📊
* Application settings and configuration 🛠️
* Error handling and notification system 🚨
* Integration with Qt framework for GUI and event handling 📊

## 🛠️ Tech Stack
* C++ programming language 📚
* Qt framework for GUI and event handling 📊
* Qt6 framework with Widgets component 📈
* CMake build system for project configuration and build 📊
* SIP protocol for VoIP communications 📞
* Qt's signal-slot mechanism for event handling and notification 📣

## 📦 Installation
To install the VoIP Application Project, follow these steps:
1. Clone the repository using Git 📚
2. Install the required dependencies, including Qt6 framework and CMake 📈
3. Configure the project using CMake 📊
4. Build the project using the configured build system 📈
5. Run the application using the built executable 📊

## 💻 Usage
To use the VoIP Application Project, follow these steps:
1. Launch the application using the executable 📊
2. Register a new user account or log in to an existing account 📝
3. Configure the application settings, including SIP account credentials and server settings 🛠️
4. Initiate a call using the call initiation feature 📞
5. Manage ongoing calls, including answering, rejecting, and terminating calls, hold call and voice off 📞
6. View recent call history and logging 📊

## 📂 Project Structure
```markdownapp
app
├── CMakeLists.txt
├── common
│   ├── errors
│   │   ├── auth_error.cpp
│   │   ├── auth_error.h
│   │   ├── call_error.cpp
│   │   └── call_error.h
│   ├── exceptions
│   │   ├── invalid_credentials_exception.cpp
│   │   ├── invalid_credentials_exception.h
│   │   ├── server_unavailable_exception.cpp
│   │   └── server_unavailable_exception.h
│   ├── states
│   │   ├── call_state.h
│   │   └── request_states.h
│   └── validation
│       ├── lexicalvalidation.cpp
│       ├── lexicalvalidation.h
│       ├── regex_patterns.h
│       ├── validation.cpp
│       └── validation.h
├── data
│   ├── CMakeLists.txt
│   ├── repositories
│   │   ├── auth
│   │   │   ├── auth_repository_impl.cpp
│   │   │   └── auth_repository_impl.h
│   │   ├── calls
│   │   │   ├── call_repository_impl.cpp
│   │   │   └── call_repository_impl.h
│   │   ├── contacts
│   │   │   ├── contact_fetcher_repository_impl.cpp
│   │   │   └── contact_fetcher_repository_impl.h
│   │   └── setting
│   │       ├── setting_repository_impl.cpp
│   │       └── setting_repository_impl.h
│   └── services
│       ├── crypto
│       │   ├── crypto.cpp
│       │   └── crypto.h
│       ├── PBX
│       │   ├── contact_fetcher_pbx.cpp
│       │   ├── contact_fetcher_pbx.h
│       │   └── pbx_api_constants.h
│       ├── setting_saver
│       │   ├── setting_saver.cpp
│       │   └── setting_saver.h
│       ├── SettingSaver
│       └── SIP
│           ├── module_sip.cpp
│           ├── module_sip.h
│           ├── my_account.cpp
│           ├── my_account.h
│           ├── my_call.cpp
│           ├── my_call.h
│           └── returning_states.h
├── domain
│   ├── controllers
│   │   ├── auth
│   │   │   ├── auth_controller.cpp
│   │   │   └── auth_controller.h
│   │   ├── calls
│   │   │   ├── call_controller.cpp
│   │   │   └── call_controller.h
│   │   ├── contacts
│   │   │   ├── contact_list_controller.cpp
│   │   │   ├── contact_list_controller.h
│   │   │   └── IContactRepository.h
│   │   ├── recent_calls
│   │   │   ├── recent_call_controller.cpp
│   │   │   └── recent_call_controller.h
│   │   └── setting
│   │       ├── setting_controller.cpp
│   │       └── setting_controller.h
│   ├── entities
│   │   ├── auth_credits.cpp
│   │   ├── auth_credits.h
│   │   ├── call_session.cpp
│   │   ├── call_session.h
│   │   ├── contact.cpp
│   │   ├── contact.h
│   │   ├── pbx_auth_credits.cpp
│   │   ├── pbx_auth_credits.h
│   │   ├── recent_call.h
│   │   ├── sip_uri.cpp
│   │   └── sip_uri.h
│   └── interfaces
│       ├── auth_repository.cpp
│       ├── auth_repository.h
│       ├── call_initiator.cpp
│       ├── call_initiator.h
│       ├── call_repository.cpp
│       ├── call_repository.h
│       ├── contact_fetcher_repository.cpp
│       ├── contact_fetcher_repository.h
│       ├── recent_call_repository.cpp
│       ├── recent_call_repository.h
│       ├── setting_repository.cpp
│       └── setting_repository.h
├── main.cpp
└── ui
    ├── model
    │   ├── auth_menu_model.cpp
    │   ├── auth_menu_model.h
    │   ├── call_menu_model.cpp
    │   ├── call_menu_model.h
    │   ├── contact_list_model.cpp
    │   ├── contact_list_model.h
    │   ├── recent_call_model.cpp
    │   ├── recent_call_model.h
    │   ├── setting_menu_model.cpp
    │   └── setting_menu_model.h
    ├── presenter
    │   ├── auth_menu_presenter.cpp
    │   ├── auth_menu_presenter.h
    │   ├── call_menu_presenter.cpp
    │   ├── call_menu_presenter.h
    │   ├── contact_list_presenter.cpp
    │   ├── contact_list_presenter.h
    │   ├── recent_call_presenter.cpp
    │   ├── recent_call_presenter.h
    │   ├── setting_menu_presenter.cpp
    │   └── setting_menu_presenter.h
    └── view
        ├── auth
        │   ├── auth_menu.cpp
        │   └── auth_menu.h
        ├── call_menu
        │   ├── call_menu.cpp
        │   └── call_menu.h
        ├── contact_list
        │   ├── contact_list.cpp
        │   └── contact_list.h
        ├── main_window
        │   ├── main_window.cpp
        │   ├── main_window.h
        │   └── mainwindow.ui
        ├── recent_calls
        │   ├── recent_calls.cpp
        │   └── recent_calls.h
        └── setting
            ├── setting_menu.cpp
            └── setting_menu.h
```

## 📸 Screenshots

<img width="757" height="717" alt="image" src="https://github.com/user-attachments/assets/0589201c-f682-42ec-a724-97f3efbda0a0" />
<img width="695" height="610" alt="image" src="https://github.com/user-attachments/assets/b956bcf6-c5ab-46e7-9891-442d629d8250" />
<img width="513" height="643" alt="image" src="https://github.com/user-attachments/assets/79b4c12f-73cc-4421-95e5-3febc3d0b7f8" />
<img width="783" height="609" alt="image" src="https://github.com/user-attachments/assets/cd91290f-9972-4f34-96ad-ffc9d826672c" />
<img width="429" height="499" alt="image" src="https://github.com/user-attachments/assets/c56b5a46-c8c3-4022-a485-e1f51a30d2d2" />







