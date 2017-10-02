# comment_stream
Prefix new lines written to std::ostreams with a comment literal.

## Example usage

    std::map<std::string, double> universe;
    universe["pi"] = 3.141592;
    universe["e"] = 1.602e-19;
    universe["hbar"] = 1.055e-34;

    // wrap comment_stream around any other ostream and provide comment string
    comment_stream cs(std::cout, "# ");

    // structured bindings require C++17, but comment_stream doesn't per se
    for (auto & [key, value] : universe) {
        cs << key << "\t=\t";
        cs << value << std::endl;
    }
    
Produces output:

    # e     =       1.602e-19
    # hbar  =       1.055e-34
    # pi    =       3.14159
