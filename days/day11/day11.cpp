#include <iostream>
#include <string>

void incrementString(std::string &input)
{
    size_t pos = input.size();

    while (pos--)
    {
        switch (input[pos])
        {
        case 'z':
            input[pos] = 'a';
            break;
        case 'h':
        case 'k':
        case 'n':
            input[pos] += 2; // Next character would be i, o or l, so advance by two.
            return;
        default:
            ++input[pos];
            return;
        }
    }
}

bool isValidPassword(const std::string &password)
{
    char prev = '\0';
    size_t straightChain = 0;
    bool straightFound = false;

    for (char ch : password)
    {
        // Check for forbidden characters
        if (ch == 'i' || ch == 'o' || ch == 'l')
            return false;

        // Check for straights
        if (!straightFound)
        {
            if (ch == prev + 1)
            {
                if (++straightChain >= 2)
                    straightFound = true;
            }
            else
                straightChain = 0;
        }

        prev = ch;
    }

    if (!straightFound)
        return false;

    // Search non-overlapping pairs
    char firstPairChar = '\0';
    for (size_t i = 0, n = password.size() - 1; i < n; ++i)
    {
        if (password[i] == password[i + 1])
        {
            if (!firstPairChar)
                firstPairChar = password[i];
            else if (password[i] != firstPairChar)
                return true;

            ++i;
        }
    }

    return false;
}

void nextPassword(std::string &password)
{
    do
        incrementString(password);
    while (!isValidPassword(password));
}

int main(int, char **)
{
    std::string input;
    std::cin >> input;
    
    nextPassword(input);
    std::cout << "Santa's next password should be: " << input << std::endl;
    
    nextPassword(input);
    std::cout << "And the one after that should be: " << input << std::endl;
}
