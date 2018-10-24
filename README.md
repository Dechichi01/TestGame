# Inventory System

Sample inventory system using in C++ **Unreal Engine 4**

## Architecture Overview ##
![Architecture_Image_Missing](ArchitectureModel.png)

## Disclaimer ##
    An inventory system would likely be a separated module in a professional project. I designed it with that in mind but **did not** created an additional module in Unreal for simplicity of workflow

## Classes Summary ##
- InventoryContainer holds a list of FSlots with several Items. Logic such as max capacity, stacking, add/remove/get items goes there.

- InventoryComponent

