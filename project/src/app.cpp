#include "app.h"

#include <iostream>
#include <string>

App::App(const std::string& filename) : diary(filename)
{
}

int App::run(int argc, char* argv[]) {
    if (argc == 1) {
        return show_usage(argv);
    }

    std::string action = argv[1];

    if (action == "add") {
        if (argc == 2) {
            return add();
        } else {
            return add(argv[2]);
        }
    } else if (action == "list") {
        list_messages();
    } else if (action == "search") {
    	if (argc == 2) {
    		return search();
    	} else {
    		search(argv[2]);
    	}
    } else {
        return show_usage(argv);
    }

    return 0;
}

int App::add() {
    std::string message;
    std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    return add(message);
}

int App::add(const std::string message) {
    diary.add(message);
    return diary.write();
}

void App::list_messages() {
    for (size_t i = 0; i < diary.messages_size; ++i) {
        const Message& message = diary.messages[i];
        std::cout << "-" << message.content << std::endl;
    }
}

int App::search() {
	std::string what;
	std::cout << "Enter a term search: ";
	std::getline(std::cin, what);

	return search(what);
}

int App::search(std::string what) {
	Message *message = diary.search(what);
	if (!message) {
		std::cout << "No match for \""<< what << "\".\n";
    	return 1;
	}

	std::cout << "\"" << what << "\" found in: \n\t# " << message->date.to_string()
			  << "\n\t- " << message->time.to_string() << message->content << std::endl;
	return 0;
}

int App::show_usage(char *argv[]) {
    std::cout << "Use:   " << argv[0] << " add <message>\n"
              << "       " << argv[0] << " list\n"
              << "       " << argv[0] << " search <search term>\n";
    return 1;
}