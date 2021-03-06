// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#include "torch/torch.h"
THIRD_PARTY_INCLUDES_END
#include "ReplayMemory.h"
#include "Dqnet.h"

/**
 * 
 */
class DQN_CAR_API NetworkInterface
{
public:
	NetworkInterface(int32 numStates, int32 numActions, float gamma, float learningRate, torch::Device device = torch::kCPU);
	~NetworkInterface();

	void Init();

	void Train(const Experience& sample);

	void CloneModel(const std::string& path);

	void SavePolicyNet(const std::string& path);
	void LoadPolicyNet(const std::string& path);

	void SaveTargetNet(const std::string& path);
	void LoadTargetNet(const std::string& path);

	void SaveOptimizer(const std::string& path);
	void LoadOptimizer(const std::string& path);

	void SaveRewardEval(std::vector<torch::Tensor>& vecRewards, const std::string& path);
	void LoadRewardEval(std::vector<torch::Tensor>& vecRewards, const std::string& path);

	inline Dqnet GetPolicyNet() const { return m_PolicyNet; }
	inline Dqnet GetTargetNet() const { return m_TargetNet; }

private:
	// do not call this function it does not work // when it works it will be made public
	//void LoadStateDict();

private:
	Dqnet m_PolicyNet;
	Dqnet m_TargetNet;

	torch::optim::Adam m_Optimizer;

	float m_Gamma = 0.99f;

	torch::Device m_Device;
	torch::Tensor m_Loss;
};
