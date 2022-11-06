#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"
#include "GameEngineFile.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(const char* _path)
{
	path_ = _path;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::GameEngineDirectory(const std::string& _path)
{
	path_ = _path;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::GameEngineDirectory(const std::string_view& _path)
{
	path_ = _path;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::GameEngineDirectory(const std::filesystem::path& _path)
{
	path_ = _path;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _other)
{
	path_ = _other.path_;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _other) noexcept
{
	path_ = _other.path_;
	if (false == std::filesystem::exists(path_))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEngineDirectory::~GameEngineDirectory()
{
}

void GameEngineDirectory::MoveToParent()
{
	path_ = path_.parent_path();
}

void GameEngineDirectory::MoveToParent(const std::string_view& _parentName)
{
	while (false == IsRoot())
	{
		this->path_ = path_.parent_path();
		if (this->GetFileName() == _parentName)
		{
			break;
		}
	}
}

bool GameEngineDirectory::MoveParentToExistChildDirectory(const std::string_view& _childName)
{
	std::string findDirectory = GameEngineString::ToUpperReturn(_childName);
	std::vector<GameEngineFile> returnVector;

	while (true)
	{
		std::filesystem::directory_iterator dirIter(this->path_);

		for (const std::filesystem::directory_entry& entry : dirIter)
		{
			if (true == entry.is_directory())
			{
				const std::string currentFileName = GameEngineString::ToUpperReturn(entry.path().filename().string());
				if (currentFileName == findDirectory)
				{
					return true;
				}
			}
		}

		if (true == this->IsRoot())
		{
			return false;
		}

		MoveToParent();
	}

	return false;
}

bool GameEngineDirectory::IsRoot() const
{
	//return "\\" == this->path_.parent_path().string();
	return this->path_.root_path() == this->path_;
	//std::filesystem::path::root_path() ���� �־��� ����� ��Ʈ ��θ� ��ȯ�ϴ� �Լ�.
}

void GameEngineDirectory::MoveToChild(const std::string_view& _childName)
{
	std::filesystem::path checkPath = this->path_;
	checkPath.append(_childName);

	if (false == std::filesystem::exists(checkPath))
	{
		MsgBoxAssert("�������� �ʴ� ����Դϴ�.");
		return;
	}

	this->path_ = checkPath;
}

std::string GameEngineDirectory::PlusFilePath(const std::string_view& _fileName)
{
	return this->GetFullPath() + "\\" + _fileName.data();
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFiles(const std::string_view& _ext /*= ""*/)
{
	std::filesystem::directory_iterator dirIter(path_);
	std::string extension = _ext.data();

	if (extension != "")
	{
		GameEngineString::ToUpper(extension);
		if (std::string::npos == extension.find("."))
		{
			extension = "." + extension;
		}
	}

	std::vector<GameEngineFile> returnVector;

	for (const std::filesystem::directory_entry& entry : dirIter)
	{
		if (true == entry.is_directory())
		{
			//���� ���丮�� ���ϵ��� �ܾ�����Ŷ�� ���⼭ ���.
			continue;
		}

		if (extension != "")
		{
			GameEnginePath newPath = entry.path();
			std::string otherExtension = GameEngineString::ToUpperReturn(newPath.GetExtention());

			if (otherExtension != extension)
			{
				continue;
			}
		}
		returnVector.push_back(GameEngineFile(entry.path()));
	}

	return returnVector;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetAllDirectories()
{
	std::filesystem::directory_iterator dirIter(path_);
	std::vector<GameEngineDirectory> returnVector;

	for (const std::filesystem::directory_entry& entry : dirIter)
	{
		if (true == entry.is_directory())
		{
			returnVector.push_back(GameEngineDirectory(entry.path()));
			continue;
		}
	}

	return returnVector;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetRecursiveAllDirectories()
{
	std::vector<GameEngineDirectory> returnVector;

	std::filesystem::recursive_directory_iterator dirIter(path_);

	for (const std::filesystem::directory_entry& entry : dirIter)
	{
		if (true == entry.is_directory())
		{
			returnVector.push_back(GameEngineDirectory(entry.path()));
		}
	}

	return returnVector;
}
