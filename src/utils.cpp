#include "homebrew/utils.hpp"



namespace homebrew
{

  std::vector<std::vector<std::string>> regex_file(const std::string& file, const std::string& regex)
  {
    std::vector<std::vector<std::string> > matches;
    std::ifstream in_f(file);
    if (!in_f.is_open())
    {
      // LOGF(INFO,"Could not open file (%s)", file);
      std::cout << "error!" << "\n";
      return  matches;
    }
    std::string contents((std::istreambuf_iterator<char>(in_f)), std::istreambuf_iterator<char>());
    in_f.close();
    std::string::const_iterator text_iter = contents.cbegin();    
    const std::regex reg(regex, std::regex::icase | std::regex::ECMAScript);
    std::smatch match;
    int match_cnt = 0;
    while (std::regex_search(text_iter, contents.cend(), match, reg))
    {
      matches.push_back(std::vector<std::string>());
      for (const auto group : match)
      {
        matches[match_cnt].push_back(group);
      }
      text_iter = match[0].second;
      match_cnt++;
    }
    return matches;
  }

  std::string make_usage_string(const std::string& program_name, const po::options_description& desc, po::positional_options_description& p)
  {
    std::vector<std::string> parts;
    parts.push_back("Usage: ");
    parts.push_back(program_name);
    size_t N = p.max_total_count();
    if(N == std::numeric_limits<unsigned>::max())
    {
      std::vector<std::string> args = _get_unlimited_positional_args(p);
      parts.insert(parts.end(), args.begin(), args.end());
    }
    else
    {
      for(size_t i = 0; i < N; ++i)
      {
        parts.push_back(p.name_for_position(i));
      }
    }
    if(desc.options().size() > 0)
    {
      parts.push_back("[options]");
    }
    std::ostringstream oss;
    std::copy(
      parts.begin(),
      parts.end(),
      std::ostream_iterator<std::string>(oss, " "));
    oss << '\n' << desc;
    return oss.str();
  }

  
  std::vector<std::string> _get_unlimited_positional_args(const po::positional_options_description& p)
  {
    assert(p.max_total_count() == std::numeric_limits<unsigned>::max());

    std::vector<std::string> parts;

    // reasonable upper limit for number of positional options:
    const int MAX = 1000; 
    std::string last = p.name_for_position(MAX);

    for(size_t i = 0; true; ++i)
    {
      std::string cur = p.name_for_position(i);
      if(cur == last)
      {
        parts.push_back(cur);
        parts.push_back('[' + cur + ']');
        parts.push_back("...");
        return parts;
      }
      parts.push_back(cur);
    }
    return parts; // never get here
  }


}
