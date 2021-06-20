// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "RenderMesh.h"

void AAIControllerBase::GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const {
	BPGetActorEyesViewPoint(out_Location, out_Rotation);
}
