//
//  echolalia.js
//
//  Created by Christian Swinehart on 2010-12-15.
//  Copyright (c) 2011 Samizdat Drafting Co. All rights reserved.
//

(function($){

  DeadSimpleRenderer = function(canvas){
    var canvas = $(canvas).get(0);
    canvas.width = document.body.clientWidth; //document.width is obsolete
    canvas.height = document.body.clientHeight; //document.height is obsolete
    var ctx = canvas.getContext("2d");
    var particleSystem = null;

    var that = {
      //
      // the particle system will call the init function once, right before the
      // first frame is to be drawn. it's a good place to set up the canvas and
      // to pass the canvas size to the particle system
      //
      init:function(system){
        // save a reference to the particle system for use in the .redraw() loop
        particleSystem = system;

        // inform the system of the screen dimensions so it can map coords for us.
        // if the canvas is ever resized, screenSize should be called again with
        // the new dimensions
        particleSystem.screenSize(canvas.width, canvas.height);
        particleSystem.screenPadding(80); // leave an extra 80px of whitespace per side
      },
      
      // 
      // redraw will be called repeatedly during the run whenever the node positions
      // change. the new positions for the nodes can be accessed by looking at the
      // .p attribute of a given node. however the p.x & p.y values are in the coordinates
      // of the particle system rather than the screen. you can either map them to
      // the screen yourself, or use the convenience iterators .eachNode (and .eachEdge)
      // which allow you to step through the actual node objects but also pass an
      // x,y point in the screen's coordinate system
      // 

      redraw:function(){
        ctx.clearRect(0,0, canvas.width, canvas.height)
        
        particleSystem.eachEdge(function(edge, pt1, pt2){
          // edge: {source:Node, target:Node, length:#, data:{}}
          // pt1:  {x:#, y:#}  source position in screen coords
          // pt2:  {x:#, y:#}  target position in screen coords

          // draw a line from pt1 to pt2
          ctx.strokeStyle = "rgba(255,255,255, .333)"
          ctx.lineWidth = 1 + 4*edge.data.weight
          ctx.beginPath()
          ctx.moveTo(pt1.x, pt1.y)
          ctx.lineTo(pt2.x, pt2.y)
          ctx.stroke()
        })

        particleSystem.eachNode(function(node, pt){
          // node: {mass:#, p:{x,y}, name:"", data:{}}
          // pt:   {x:#, y:#}  node position in screen coords

          // draw a rectangle centered at pt
          var w = 10
          ctx.fillStyle = node.data.color;
          //ctx.fillRect(pt.x-w/2, pt.y-w/2, w,w);
          ctx.beginPath();
          ctx.arc(pt.x, pt.y,w,0,2*Math.PI);
          ctx.fill();
          ctx.strokeStyle = '#DDD';
          ctx.stroke();
          ctx.font = "bold 11px Arial";
          ctx.textAlign = "center";
          ctx.fillStyle = "#000";
          ctx.fillText(node.name||"", pt.x, pt.y+4);
        })    			
      }
    }
    return that
  }    

  $(document).ready(function(){
    var sys = arbor.ParticleSystem();// create the system with sensible repulsion/stiffness/friction
    sys.parameters({stiffness:100,friction:0.98,repulsion:2000,gravity:true});
    sys.renderer = DeadSimpleRenderer("#viewport");// our newly created renderer will have its .init() method called shortly by sys...
    // load the data into the particle system as is (since it's already formatted correctly for .grafting)
    var data = $.getJSON("data/graph.json",function(data){
      sys.graft({nodes:data.nodes, edges:data.edges})
    });
  })


})(this.jQuery)