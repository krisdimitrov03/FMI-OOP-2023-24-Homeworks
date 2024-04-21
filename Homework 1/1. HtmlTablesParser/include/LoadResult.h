#pragma once

enum class LoadResult {
	OK,
	NullPtrFileName,
	FileOpenFailed,
	IncorrectTableFormat,
	TableSizeOverflow
};