/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include <sstream>
#include <vector>
#include "script.h"

class TreeNode
{
public:
	TreeNode* parent = NULL;

	std::string value;
	bool isRoot = false;
	std::vector<TreeNode*> children;

	bool hasChildren()
	{
		return children.size() > 0;
	};

	inline TreeNode* findChildWithValue(std::string value)
	{
		for each (TreeNode *child  in children)
		{
			if (child->value.compare(value) == 0)
			{
				return child;
			}
		}
		return NULL;
	}

	inline TreeNode* addChild(std::string value)
	{
		TreeNode *newChild = new TreeNode();
		newChild->value = value;
		newChild->parent = this;
		children.push_back(newChild);
		return newChild;
	}

	std::string getFullDict(bool includeLeaf=false)
	{
		std::stringstream ss;

		if (parent != NULL)
		{
			ss << parent->getFullDict(includeLeaf);
		}
		if ((this->hasChildren() || includeLeaf) && parent != NULL && !parent->isRoot)
		{
			ss << "@";
		}
		if ((this->hasChildren() || includeLeaf))
		{
			ss << value;
		}

		auto result = ss.str();
		return result;
	}

	inline ~TreeNode()
	{
		for (std::vector<TreeNode*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			delete (*it);
		}
		children.clear();
	};
};

void build_anim_tree();

TreeNode* build_anim_tree(std::vector<std::string> input, bool includeAnim=true);

TreeNode* build_anim_tree_with_suffix_filter(std::string filter);

TreeNode* build_anim_tree_with_prefix_filter(std::string filter);

bool process_anims_menu();

bool process_anims_menu_top();

void replay_last_anim();

void do_play_anim(Ped playerPed, char* dict, char* anim, int mode);

void cleanup_anims();

void update_anims_features(BOOL bPlayerExists, Ped playerPed);

void add_anims_generic_settings(std::vector<StringPairSettingDBRow>* results);

void add_anims_feature_enablements(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_anims(std::vector<StringPairSettingDBRow>* settings);

bool process_scenarios_menu_l1();

bool process_clipset_menu();