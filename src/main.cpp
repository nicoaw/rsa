#include "Crypt.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/program_options.hpp>
#include <algorithm>
#include <fstream>
#include <iterator>

namespace mp = boost::multiprecision;
namespace po = boost::program_options;

int main(int argc, char** argv)
{
	po::options_description commandLineOptions
	{
		"Usage: rsa [options]\n"
		"Where options are"
	};
	commandLineOptions.add_options()
		("decrypt,d", po::value<std::string>(), "specifies the input file for decryption")
		("encrypt,e", po::value<std::string>(), "specifies the input file for encryption")
		("help,h", "produce help messages")
		("key,k", po::value<std::string>(), "specifies the key file")
		("output,o", po::value<std::string>(), "specify the output file")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, commandLineOptions), vm);
	po::notify(vm);

	// Run decryption
	if(vm.count("decrypt") && vm.count("key") && !vm.count("encrypt"))
	{
		const std::string inFileName = vm["decrypt"].as<std::string>();
		const std::string keyFileName = vm["key"].as<std::string>();
		const std::string outFileName = vm.count("output") ? vm["output"].as<std::string>() : inFileName;

		// Get key parameters
		std::ifstream keyFile{keyFileName};
		mp::cpp_int p, q, e;
		keyFile >> p >> q >> e;
		keyFile.close();

		// Decrypt data
		std::ifstream inFile{inFileName};
		std::ofstream outFile{outFileName};
		std::istream_iterator<mp::cpp_int> inFileFirst{inFile}, inFileLast;
		std::ostream_iterator<char> outFileResult{outFile};
		RSAKey privateKey = makePrivateKey(p, q, e);
		std::transform(inFileFirst, inFileLast, outFileResult, [&privateKey](const auto& cypher) { return (char) decrypt(privateKey, cypher); });
	}
	// Run encryption
	else if(vm.count("encrypt") && vm.count("key") && !vm.count("decrypt"))
	{
		const std::string inFileName = vm["encrypt"].as<std::string>();
		const std::string keyFileName = vm["key"].as<std::string>();
		const std::string outFileName = vm.count("output") ? vm["output"].as<std::string>() : inFileName;

		// Get key parameters
		std::ifstream keyFile{keyFileName};
		mp::cpp_int n, e;
		keyFile >> n >> e;
		keyFile.close();

		// Encrypt data
		std::ifstream inFile{inFileName};
		std::ofstream outFile{outFileName};
		std::istream_iterator<char> inFileFirst{inFile}, inFileLast;
		std::ostream_iterator<mp::cpp_int> outFileResult{outFile, " "};
		RSAKey publicKey = makePublicKey(n, e);
		std::noskipws(inFile);
		std::transform(inFileFirst, inFileLast, outFileResult, [&publicKey](char plain) { return encrypt(publicKey, plain); });
	}
	// Invalid arguments or specified help
	else
		std::cout << commandLineOptions << std::endl;

	return 0;
}
