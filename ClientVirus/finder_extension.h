#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <vector>

class FinderExtension final{
private:
	std::set<std::string> extensions_ = {".apk"};

	std::string finder_path_ = "C:\\Users\\Public";

	std::vector<std::string> paths_ = {};
private:
	bool ValidateExtension(const std::string& str) {
		return *str.begin() == '.';
	}

public:
	FinderExtension() = default;
	FinderExtension(const std::string& path) {
		finder_path_.copy(const_cast<char*>(path.c_str()), path.size());
	}

	void SetExtensions(const std::set<std::string>& extensions) {
		for (auto extension : extensions) {
			AddExtension(extension);
		}
	}
	void AddExtension(const std::string& extension) {
		if (ValidateExtension(extension))
			extensions_.insert(extension);
	}
	
	void FindPaths() {
		FindPaths(finder_path_);
	}

	void FindPaths(const std::string& finder_path) {
		std::string path("C:\\Users\\Public");
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			auto extension = p.path().extension();
			std::string ext(extension.begin(), extension.end());
			if (extensions_.find(ext) != extensions_.end())
				paths_.push_back(ext);
		}
	}

	std::vector<std::string> GetPaths() {
		return paths_;
	}
};